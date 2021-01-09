#ifdef _WIN32
#include <io.h>
#include <malloc.h>
#endif
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <memory.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "Table.h"

#ifndef SEEK_SET
#define SEEK_SET 0
#endif

extern int errno;

#ifdef _WIN32
#define CREATE_FLAGS _O_CREAT|_O_RDWR|_O_BINARY
#define PERMISSION_FLAGS _S_IREAD|_S_IWRITE
#define OPEN_FLAGS _O_RDWR|_O_BINARY
#else
#define CREATE_FLAGS O_CREAT|O_RDWR
#define PERMISSION_FLAGS S_IREAD|S_IWRITE
#define OPEN_FLAGS O_RDWR
#endif

/* FILE MAGIC - this text is written to the beginning of data file */
static char FILE_SIGNATURE[] = "\033\032DataFile\033\032~~~";

/********************************************************/
/*   table file header structure						*/
/* |-------------|------------|-------|.....|-------|	*/
/*   FILE_SIGNAT    TableInfo    Fld1          FldN		*/
/********************************************************/

typedef struct {
	char fieldName [MaxFieldNameLen];
	enum FieldType type;
	long len;
	char * pNewValue;
	char * pEditValue;
} FieldStruct;

struct Table {
	int fd;
	FieldStruct * pFieldStruct;
	struct TableInfo {
		long dataOffset;
		long fieldNumber; /* duplicates pFieldStruct->numOfFields */
		long recordSize;
		long totalRecordNumber; /* including deleted records */
		long recordNumber;
		long firstRecordOffset;
		long lastRecordOffset;
		long firstDeletedOffset;
	} tableInfo;
	long currentPos;
	Bool editFlag;
	struct links {
		long prevOffset;
		long nextOffset;
	} links;
};


/* Возможные сообщения об ошибках */
char* ErrorText[]=
		   { "Success.",
		     "Can't create table.",
		     "Can't open table.",
		     "Field not found.",
			 "Bad table handle",
			 "Wrong arguments",
			 "Can't set file position",
			 "File write error",
			 "File read error",
			 "Table data corrupted",
			 "Can't create table handle",
			 "Can't delete or open read-only file",
			 "Illegal file name",
			 "Can't delete table",
			 "File data corrupted",
			 "Bad File Position",
			 "Wrong field type",
			 "Text value exceeds field length",
			 "Current record is not edited",
		  };

/*  static function prototypes */

enum Direction {
	LINK_PREV,
	LINK_NEXT
};

static enum Errors GetCurrentRecord (struct Table * tabHandle);
static enum Errors PutCurrentRecord (struct Table * tabHandle);
static enum Errors PutNewRecord (struct Table *  tabHandle, long position, struct links * links);
static enum Errors ModifyLinks (struct Table *  tabHandle, long position, long value, enum Direction dir);
static enum Errors GetInsertPos (struct Table * tabHandle, long * position);
static enum Errors GetLinks (struct Table * tabHandle, long position, struct links * links);
static enum Errors WriteHeader (struct Table * tabHandle);
static enum Errors ReadHeader (struct Table * tabHandle);
static struct Table * CreateTableHandle (struct TableStruct * tableStruct);
static struct Table * AllocateTableHandle (void);
static void DeleteTableHandle (struct Table * tabHandle);
static enum Errors AllocateBuffers (struct Table * tabHandle);
static void DeallocateBuffers (struct Table * tabHandle);
static enum Errors AddRecToDeleted (struct Table * tabHandle);

/*  library function definitions */

enum Errors createTable(char *tableName, struct TableStruct *tableStruct)
{
	int fd;
	enum Errors retval;
	struct Table * tabHandle;

	if (!tableName || !tableStruct) return BadArgs;

	fd = open (tableName, CREATE_FLAGS, PERMISSION_FLAGS);
	if (fd < 0)
		switch(errno) {
		case EACCES: return ReadOnlyFile;
		case ENOENT: return BadFileName;
		default:
			return CantCreateTable;
		}

	if (tableStruct->numOfFields <= 0 || !tableStruct->fieldsDef) return CorruptedData;

	tabHandle = CreateTableHandle (tableStruct);

	if (!tabHandle) {
		close (fd);
		return CantCreateHandle;
	}

	tabHandle->fd = fd;
	retval = WriteHeader (tabHandle);

	DeleteTableHandle (tabHandle);

	return retval;
}

enum Errors deleteTable(char *tableName)
{
	if (!tableName) return BadArgs;
	if (!unlink (tableName)) return OK;
	switch(errno) {
	case EACCES : return ReadOnlyFile;
	case ENOENT : return BadFileName;
	default : return CantDeleteTable;
	}
}

enum Errors openTable(char *tableName, THandle *tableHandle)
{
	int fd;
	enum Errors retval;
	struct Table * tabHandle;

	if (!tableName || !tableHandle) return BadArgs;

	*tableHandle = NULL;

	fd = open (tableName, OPEN_FLAGS);
	if (fd < 0)
		switch(errno) {
		case EACCES: return ReadOnlyFile;
		case ENOENT: return BadFileName;
		default:
			return CantOpenTable;
		}
	tabHandle = AllocateTableHandle ();
	if (!tabHandle) {
		close (fd);
		return CantCreateHandle;
	}

	tabHandle->fd = fd;
	retval = ReadHeader (tabHandle);
	if (retval != OK) {
		DeleteTableHandle (tabHandle);
		return retval;
	}

	retval = AllocateBuffers (tabHandle);
	if (retval != OK) {
		DeleteTableHandle (tabHandle);
		return retval;
	}

	tabHandle->currentPos = tabHandle->tableInfo.firstRecordOffset;

	if (tabHandle->currentPos >= tabHandle->tableInfo.dataOffset)  {
		retval = GetCurrentRecord (tabHandle);
		if (retval != OK) {
			DeleteTableHandle (tabHandle);
			return retval;
		}
	}

	*tableHandle = tabHandle;
	return OK;
}

enum Errors closeTable(THandle tableHandle)
{
	enum Errors retval = OK;

	if (!tableHandle) return BadHandle;
	if (tableHandle->fd >= 0) {
		retval = WriteHeader (tableHandle);
	}
	DeleteTableHandle(tableHandle);
	return retval;
}

enum Errors moveFirst(THandle tableHandle)
{
	if (!tableHandle || tableHandle->fd < 0) return BadHandle;

	tableHandle->currentPos = tableHandle->tableInfo.firstRecordOffset;
	if (tableHandle->tableInfo.recordNumber == 0) return OK;

	return GetCurrentRecord (tableHandle);
}

enum Errors moveLast(THandle tableHandle)
{
	if (!tableHandle || tableHandle->fd < 0) return BadHandle;

	tableHandle->currentPos = tableHandle->tableInfo.lastRecordOffset;
	if (tableHandle->tableInfo.recordNumber == 0) return OK;

	return GetCurrentRecord (tableHandle);
}

enum Errors moveNext(THandle tableHandle)
{
	if (!tableHandle || tableHandle->fd < 0) return BadHandle;
	switch (tableHandle->currentPos){
	case -1: /* beforeFirst */
		tableHandle->currentPos = tableHandle->tableInfo.firstRecordOffset;
		return GetCurrentRecord (tableHandle);
	case 0:  /* after last */
		return BadPos;
	default:
		tableHandle->currentPos = tableHandle->links.nextOffset;
		if (tableHandle->currentPos >= tableHandle->tableInfo.dataOffset) {
			return GetCurrentRecord (tableHandle);
		} else
			return OK;
	}
}

enum Errors movePrevios(THandle tableHandle)
{
	if (!tableHandle || tableHandle->fd < 0) return BadHandle;
	switch (tableHandle->currentPos){
	case -1: /* beforeFirst */
		return BadPos;
	case 0:  /* after last */
		tableHandle->currentPos = tableHandle->tableInfo.lastRecordOffset;
		return GetCurrentRecord (tableHandle);
	default:
		tableHandle->currentPos = tableHandle->links.prevOffset;
		if (tableHandle->currentPos >= tableHandle->tableInfo.dataOffset) {
			return GetCurrentRecord (tableHandle);
		} else
			return OK;
	}
}

Bool beforeFirst(THandle tableHandle)
{
	if (!tableHandle || tableHandle->fd < 0) return FALSE;
	switch (tableHandle->currentPos){
	case -1: /* beforeFirst */
		return TRUE;
	case 0:  /* after last */
		return tableHandle->tableInfo.recordNumber == 0;
	default:
		return FALSE;
	}
}

Bool afterLast(THandle tableHandle)
{
	if (!tableHandle || tableHandle->fd < 0) return FALSE;
	switch (tableHandle->currentPos){
	case -1: /* beforeFirst */
		return tableHandle->tableInfo.recordNumber == 0;
	case 0:  /* after last */
		return TRUE;
	default:
		return FALSE;
	}
}

enum Errors getText(THandle tableHandle, char *fieldName, char **pvalue)
{
	int i;

	if (!tableHandle) return BadHandle;
	if (!fieldName || !pvalue) return BadArgs;

	for (i = 0; i < tableHandle->tableInfo.fieldNumber; i++)
		if (strcmp(fieldName, tableHandle->pFieldStruct[i].fieldName) == 0) {
			if (tableHandle->pFieldStruct[i].type != Text) return BadFieldType;
			*pvalue = tableHandle->pFieldStruct[i].pEditValue;
			return OK;
		}
	return FieldNotFound;
}

enum Errors getLong(THandle tableHandle, char *fieldName, long *pvalue)
{
	int i;

	if (!tableHandle) return BadHandle;
	if (!fieldName || !pvalue) return BadArgs;

	for (i = 0; i < tableHandle->tableInfo.fieldNumber; i++)
		if (strcmp(fieldName, tableHandle->pFieldStruct[i].fieldName) == 0) {
			if (tableHandle->pFieldStruct[i].type != Long) return BadFieldType;
			memcpy (pvalue, tableHandle->pFieldStruct[i].pEditValue, sizeof(long));
			return OK;
		}
	return FieldNotFound;
}

enum Errors startEdit(THandle tableHandle)
{
	if (!tableHandle) return BadHandle;
	if (tableHandle->currentPos < tableHandle->tableInfo.dataOffset) return BadPos;
	tableHandle->editFlag = TRUE;
	return OK;
}

enum Errors putText(THandle tableHandle, char *fieldName, char *value)
{
	int i;

	if (!tableHandle) return BadHandle;
	if (!fieldName || !value) return BadArgs;

	for (i = 0; i < tableHandle->tableInfo.fieldNumber; i++)
		if (strcmp(fieldName, tableHandle->pFieldStruct[i].fieldName) == 0) {
			if (tableHandle->pFieldStruct[i].type != Text) return BadFieldType;
			if (strlen (value) >= (unsigned)tableHandle->pFieldStruct[i].len) return BadFieldLen;
			strcpy (tableHandle->pFieldStruct[i].pEditValue, value);
			return OK;
		}
	return FieldNotFound;
}

enum Errors putLong(THandle tableHandle, char *fieldName, long value)
{
	int i;

	if (!tableHandle) return BadHandle;
	if (!fieldName) return BadArgs;

	for (i = 0; i < tableHandle->tableInfo.fieldNumber; i++)
		if (strcmp(fieldName, tableHandle->pFieldStruct[i].fieldName) == 0) {
			if (tableHandle->pFieldStruct[i].type != Long) return BadFieldType;
			memcpy (tableHandle->pFieldStruct[i].pEditValue, &value, sizeof (long));
			return OK;
		}
	return FieldNotFound;
}

enum Errors finishEdit(THandle tableHandle)
{
	if (!tableHandle) return BadHandle;
	if (!tableHandle->editFlag) return NoEditing;
	tableHandle->editFlag = FALSE;
	return PutCurrentRecord (tableHandle);
}

enum Errors createNew(THandle tableHandle)
{
	int i;
	if (!tableHandle) return BadHandle;
	for (i = 0; i < tableHandle->tableInfo.fieldNumber; i++) {
		memset (tableHandle->pFieldStruct[i].pNewValue, 0, tableHandle->pFieldStruct[i].len);
	}
	return OK;
}

enum Errors putTextNew(THandle tableHandle, char *fieldName, char *value)
{
	int i;

	if (!tableHandle) return BadHandle;
	if (!fieldName || !value) return BadArgs;

	for (i = 0; i < tableHandle->tableInfo.fieldNumber; i++)
		if (strcmp(fieldName, tableHandle->pFieldStruct[i].fieldName) == 0) {
			if (tableHandle->pFieldStruct[i].type != Text) return BadFieldType;
			if (strlen (value) >= (unsigned)tableHandle->pFieldStruct[i].len) return BadFieldLen;
			strcpy (tableHandle->pFieldStruct[i].pNewValue, value);
			return OK;
		}
	return FieldNotFound;
}

enum Errors putLongNew(THandle tableHandle, char * fieldName, long value)
{
	int i;

	if (!tableHandle) return BadHandle;
	if (!fieldName) return BadArgs;

	for (i = 0; i < tableHandle->tableInfo.fieldNumber; i++)
		if (strcmp(fieldName, tableHandle->pFieldStruct[i].fieldName) == 0) {
			if (tableHandle->pFieldStruct[i].type != Long) return BadFieldType;
			memcpy (tableHandle->pFieldStruct[i].pNewValue, &value, sizeof (long));
			return OK;
		}
	return FieldNotFound;
}

enum Errors insertNew(THandle tableHandle)
{
	long position;
	struct links links;
	enum Errors retval;

	if (!tableHandle || tableHandle->fd < 0) return BadHandle;
	retval = GetInsertPos (tableHandle, &position);
	if (retval != OK) return retval;
	retval = GetLinks (tableHandle, tableHandle->links.prevOffset, &links);
	if (retval != OK) return retval;
	links.nextOffset = tableHandle->currentPos;
	if (links.nextOffset == -1) links.nextOffset = 0;
	retval = PutNewRecord (tableHandle, position, &links);
	if (retval != OK) return retval;
	retval = ModifyLinks (tableHandle, tableHandle->currentPos, position, LINK_PREV);
	if (retval != OK) return retval;
	retval = ModifyLinks (tableHandle, tableHandle->links.prevOffset, position, LINK_NEXT);
	if (retval != OK) return retval;
	if (tableHandle->tableInfo.recordNumber == 0) {
		tableHandle->tableInfo.firstRecordOffset = position;
		tableHandle->tableInfo.lastRecordOffset = position;
	} else if (tableHandle->links.prevOffset == -1) {
		tableHandle->tableInfo.firstRecordOffset = position;
	}
	tableHandle->tableInfo.recordNumber++;

	return OK;
}

enum Errors insertaNew(THandle tableHandle)
{
	long position;
	struct links links;
	enum Errors retval;

	if (!tableHandle || tableHandle->fd < 0) return BadHandle;
	retval = GetInsertPos (tableHandle, &position);
	if (retval != OK) return retval;

	links.nextOffset = tableHandle->tableInfo.firstRecordOffset;
	if (links.nextOffset == -1) links.nextOffset = 0;
	links.prevOffset = -1;
	retval = PutNewRecord (tableHandle, position, &links);
	if (retval != OK) return retval;
	retval = ModifyLinks (tableHandle, tableHandle->tableInfo.firstRecordOffset, position, LINK_PREV);
	if (retval != OK) return retval;
	if (tableHandle->tableInfo.recordNumber == 0) {
		tableHandle->tableInfo.lastRecordOffset = position;
	}
	tableHandle->tableInfo.recordNumber++;
	tableHandle->tableInfo.firstRecordOffset = position;


	return OK;
}

enum Errors insertzNew(THandle tableHandle)
{
	long position;
	struct links links;
	enum Errors retval;

	if (!tableHandle || tableHandle->fd < 0) return BadHandle;
	retval = GetInsertPos (tableHandle, &position);
	if (retval != OK) return retval;
	/* insert at the end */
	links.nextOffset = 0;
	links.prevOffset = tableHandle->tableInfo.lastRecordOffset;
	if (links.prevOffset == 0) links.prevOffset = -1;
	retval = PutNewRecord (tableHandle, position, &links);
	if (retval != OK) return retval;
	retval = ModifyLinks (tableHandle, tableHandle->tableInfo.lastRecordOffset, position, LINK_NEXT);
	if (retval != OK) return retval;
	if (tableHandle->tableInfo.recordNumber == 0) {
		tableHandle->tableInfo.firstRecordOffset = position;
	}
	tableHandle->tableInfo.recordNumber++;
	tableHandle->tableInfo.lastRecordOffset = position;
	return OK;

}

char *getErrorString(enum Errors code)
{
	return ErrorText[code];
}

enum Errors getFieldLen(THandle tableHandle,char*fieldName,unsigned *plen)
{
	int i;

	if (!tableHandle) return BadHandle;
	if (!fieldName || !plen) return BadArgs;

	for (i = 0; i < tableHandle->tableInfo.fieldNumber; i++)
		if (strcmp(fieldName, tableHandle->pFieldStruct[i].fieldName) == 0) {
			*plen = tableHandle->pFieldStruct[i].len;
			if (tableHandle->pFieldStruct[i].type == Text) *plen = *plen-1;
			return OK;
		}
	return FieldNotFound;
}

enum Errors getFieldType(THandle tableHandle, char *fieldName, enum FieldType *ptype)
{
	int i;

	if (!tableHandle) return BadHandle;
	if (!fieldName || !ptype) return BadArgs;

	for (i = 0; i < tableHandle->tableInfo.fieldNumber; i++)
		if (strcmp(fieldName, tableHandle->pFieldStruct[i].fieldName) == 0) {
			*ptype = tableHandle->pFieldStruct[i].type;
			return OK;
		}
	return FieldNotFound;

}

enum Errors getFieldsNum(THandle tableHandle, unsigned *pNum)
{
	if (!tableHandle) return BadHandle;
	if (!pNum) return BadArgs;

	*pNum = tableHandle->tableInfo.fieldNumber;
	return OK;
}

enum Errors getFieldName(THandle tableHandle, unsigned index, char **pFieldName)
{
	if (!tableHandle) return BadHandle;
	if (!pFieldName) return BadArgs;

	*pFieldName = tableHandle->pFieldStruct[index].fieldName;
	return OK;
}


enum Errors deleteRec(THandle tableHandle)
{
	if (!tableHandle || tableHandle->fd < 0) return BadHandle;
	if (tableHandle->currentPos < tableHandle->tableInfo.firstRecordOffset)
		return BadPosition;
	return AddRecToDeleted(tableHandle);
}

/*  internal function definitions */

/* helper macros */
#define MOVE_POS(pos) \
	if (lseek(tabHandle->fd, (pos), SEEK_SET)!=(int)(pos)) return CantMoveToPos;

#define WRITE_DATA(buf,size) \
	if (write(tabHandle->fd,(buf),(size))!=(int)(size)) return CantWriteData;

#define READ_DATA(buf,size) \
	if (read(tabHandle->fd,(buf),(size))!=(int)(size)) return CantReadData;

static enum Errors WriteHeader (struct Table * tabHandle)
{
	MOVE_POS (0);
	WRITE_DATA (FILE_SIGNATURE, sizeof (FILE_SIGNATURE));
	WRITE_DATA (&tabHandle->tableInfo, sizeof (struct TableInfo));
	if (tabHandle->pFieldStruct) {
		WRITE_DATA (tabHandle->pFieldStruct, sizeof (FieldStruct) * tabHandle->tableInfo.fieldNumber);
	} else
	  return CantWriteData;

	return OK;
}

static struct Table * AllocateTableHandle ()
{
	struct Table * handle;

	handle = (struct Table *) calloc (1, sizeof (struct Table));
	if (!handle) return NULL;

	handle->fd = -1;
	handle->pFieldStruct = NULL;
	handle->currentPos = -1;

	handle->tableInfo.recordNumber = 0;
	handle->tableInfo.totalRecordNumber = 0;
	handle->tableInfo.firstRecordOffset = -1;
	handle->tableInfo.firstDeletedOffset = -1;
	handle->tableInfo.lastRecordOffset = 0;
	handle->tableInfo.fieldNumber = 0;
	handle->tableInfo.recordSize = 0;
	handle->tableInfo.dataOffset = 0;
	handle->links.prevOffset = -1;
	handle->links.nextOffset = 0;
	handle->editFlag = FALSE;
	return handle;
}

static struct Table * CreateTableHandle (struct TableStruct * tableStruct)
{
	struct Table * handle;
	unsigned i;
	long RecSize = 0;

	handle = AllocateTableHandle ();
	if (!handle) return NULL;

	/* copy structure and count record size */
	handle->tableInfo.fieldNumber = tableStruct->numOfFields;
	handle->pFieldStruct = (FieldStruct *) calloc (tableStruct->numOfFields, sizeof (FieldStruct));
	if (!handle->pFieldStruct) {
		DeleteTableHandle (handle);
		return NULL;
	}
	for (i = 0; i < tableStruct->numOfFields; i++) {
		strcpy(handle->pFieldStruct[i].fieldName, tableStruct->fieldsDef[i].name);
		handle->pFieldStruct[i].type = tableStruct->fieldsDef[i].type;
		switch(tableStruct->fieldsDef[i].type) {
		case Long:
			handle->pFieldStruct[i].len = sizeof (long);
			RecSize += sizeof (long);
			break;
		case Text:
			if (!tableStruct->fieldsDef[i].len) {
				DeleteTableHandle (handle);
				return NULL;
			}
			handle->pFieldStruct[i].len = tableStruct->fieldsDef[i].len+1;
			RecSize += tableStruct->fieldsDef[i].len+1;
			break;
		}
	}

	handle->tableInfo.recordSize = RecSize;
	handle->tableInfo.dataOffset = sizeof (FILE_SIGNATURE) +
		sizeof (struct TableInfo) + handle->tableInfo.fieldNumber * sizeof (FieldStruct);

	return handle;
}

static void DeleteTableHandle (struct Table * tabHandle)
{
	if (tabHandle->fd >= 0) close (tabHandle->fd);
	DeallocateBuffers (tabHandle);
	free (tabHandle->pFieldStruct);
	free (tabHandle);
}

static enum Errors AllocateBuffers (struct Table * tabHandle)
{
	int i;

	if (!tabHandle->pFieldStruct) return BadHandle;
	for (i = 0; i < tabHandle->tableInfo.fieldNumber; i++) {
		tabHandle->pFieldStruct[i].pNewValue = (char *)malloc(tabHandle->pFieldStruct[i].len);
		tabHandle->pFieldStruct[i].pEditValue = (char *)malloc(tabHandle->pFieldStruct[i].len);
		if (!tabHandle->pFieldStruct[i].pNewValue || !tabHandle->pFieldStruct[i].pEditValue)
			return CantCreateHandle;
	}
	return OK;
}

static void DeallocateBuffers (struct Table * tabHandle)
{
	int i;

	if (!tabHandle->pFieldStruct) return;
	for (i = 0; i < tabHandle->tableInfo.fieldNumber; i++) {
		if (tabHandle->pFieldStruct[i].pNewValue) free(tabHandle->pFieldStruct[i].pNewValue);
		if (tabHandle->pFieldStruct[i].pEditValue) free(tabHandle->pFieldStruct[i].pEditValue);
	}
}

static enum Errors ReadHeader (struct Table * tabHandle)
{
	char FileSig[sizeof(FILE_SIGNATURE)];

	MOVE_POS (0);
	READ_DATA (FileSig, sizeof (FILE_SIGNATURE));
	if (strcmp(FileSig, FILE_SIGNATURE)) return CorruptedFile;
	READ_DATA (&tabHandle->tableInfo, sizeof (struct TableInfo));

	if (tabHandle->tableInfo.fieldNumber <= 0) return CorruptedFile;
	tabHandle->pFieldStruct = (FieldStruct *)calloc (tabHandle->tableInfo.fieldNumber, sizeof (FieldStruct));
	if (!tabHandle->pFieldStruct) return CantReadData;
	READ_DATA (tabHandle->pFieldStruct, sizeof (FieldStruct) * tabHandle->tableInfo.fieldNumber);
	return OK;
}

static enum Errors GetCurrentRecord (struct Table * tabHandle)
{
	int i;

	if (tabHandle->currentPos < tabHandle->tableInfo.dataOffset) return BadPos;
	MOVE_POS (tabHandle->currentPos);
	READ_DATA (&tabHandle->links, sizeof (tabHandle->links));
	for (i = 0; i < tabHandle->tableInfo.fieldNumber; i++) {
		READ_DATA (tabHandle->pFieldStruct[i].pEditValue, tabHandle->pFieldStruct[i].len);
	}
	return OK;
}

static enum Errors GetInsertPos (struct Table * tabHandle, long * position)
{
	struct links links;

	if (tabHandle->tableInfo.firstDeletedOffset >= tabHandle->tableInfo.dataOffset) {
		*position = tabHandle->tableInfo.firstDeletedOffset;
		MOVE_POS (*position);
		READ_DATA (&links, sizeof (struct links));
		if (links.prevOffset != -1) return CorruptedFile;
		tabHandle->tableInfo.firstDeletedOffset = links.nextOffset;
	} else {
		/* no deleted records - position at the end of file */
		*position = tabHandle->tableInfo.dataOffset + tabHandle->tableInfo.totalRecordNumber *
			      (tabHandle->tableInfo.recordSize + sizeof (struct links));
		MOVE_POS (*position);
		tabHandle->tableInfo.totalRecordNumber++;
	}
	return OK;
}

static enum Errors GetLinks (struct Table * tabHandle, long position, struct links * links)
{
	if (position == 0 || position == -1) {
		links->prevOffset = -1;
		links->nextOffset = 0;
	} else {
	  MOVE_POS (position);
	  READ_DATA (links, sizeof (struct links));
	}
	return OK;
}

static enum Errors ModifyLinks (struct Table *  tabHandle, long position, long value, enum Direction dir)
{
	long posToWrite = 0;

	if (position != 0 && position != -1) {
		switch (dir) {
		case LINK_PREV: posToWrite = position;
			break;
		case LINK_NEXT: posToWrite = position + sizeof (long);
			break;
		}
		MOVE_POS (posToWrite);
		WRITE_DATA (&value, sizeof (value));
	}
	return OK;
}

static enum Errors PutNewRecord (struct Table * tabHandle, long position, struct links * links)
{
	int i;

	MOVE_POS (position);
	WRITE_DATA (links, sizeof (struct links));
	for (i = 0; i < tabHandle->tableInfo.fieldNumber; i++) {
		WRITE_DATA (tabHandle->pFieldStruct[i].pNewValue, tabHandle->pFieldStruct[i].len);
	}
	return OK;
}

static enum Errors PutCurrentRecord (struct Table * tabHandle)
{
	int i;

	MOVE_POS (tabHandle->currentPos);
	WRITE_DATA (&tabHandle->links, sizeof (struct links));
	for (i = 0; i < tabHandle->tableInfo.fieldNumber; i++) {
		WRITE_DATA (tabHandle->pFieldStruct[i].pEditValue, tabHandle->pFieldStruct[i].len);
	}
	return OK;
}

static enum Errors AddRecToDeleted (struct Table * tabHandle)
{
	static unsigned long DELETE_MARK = ~0;
	// insert record to the deleted list
	MOVE_POS (tabHandle->currentPos);
	WRITE_DATA (&DELETE_MARK, sizeof DELETE_MARK);
	WRITE_DATA(&tabHandle->tableInfo.firstDeletedOffset, sizeof(tabHandle->tableInfo.firstDeletedOffset));
	tabHandle->tableInfo.firstDeletedOffset = tabHandle->currentPos;
	tabHandle->tableInfo.recordNumber--;
	// modify prev and next links
	if (tabHandle->links.prevOffset == -1) { // first record is deleted
		tabHandle->tableInfo.firstRecordOffset = tabHandle->links.nextOffset;
		if (tabHandle->tableInfo.recordNumber == 0) {
			tabHandle->tableInfo.firstRecordOffset = -1; // no more records
			tabHandle->tableInfo.lastRecordOffset = 0; // no more records
		}
	} else {
		MOVE_POS(tabHandle->links.prevOffset + sizeof(tabHandle->links.prevOffset));
		WRITE_DATA(&tabHandle->links.nextOffset, sizeof(tabHandle->links.nextOffset));
	}
	if (tabHandle->links.nextOffset == 0) { // last record is deleted
		tabHandle->tableInfo.lastRecordOffset = tabHandle->links.prevOffset;
		if (tabHandle->tableInfo.recordNumber == 0) {
			tabHandle->tableInfo.firstRecordOffset = -1; // no more records
			tabHandle->tableInfo.lastRecordOffset = 0; // no more records
		}
	} else {
		MOVE_POS(tabHandle->links.nextOffset);
		WRITE_DATA(&tabHandle->links.prevOffset, sizeof(tabHandle->links.prevOffset));
	}
	return OK;
}
int main(int argc, char *argv[])
{

    return 0;
}
