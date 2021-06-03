#if !defined(_Table_h_)
#define _Table_h

#define MaxFieldNameLen 30 /* Максимальное число символов в названии поля */

enum Errors /* Определяет возможные коды ошибок при работе с таблицами */
{
  OK,             /* Ошибок нет */
  CantCreateTable,
  CantOpenTable,
  FieldNotFound,
  BadHandle,
  BadArgs,
  CantMoveToPos,
  CantWriteData,
  CantReadData,
  CorruptedData,
  CantCreateHandle,
  ReadOnlyFile,
  BadFileName,
  CantDeleteTable,
  CorruptedFile,
  BadPos,
  BadFieldType,
  BadFieldLen,
  NoEditing,
  BadPosition,
};

/* Возможные сообщения об ошибках */
extern char* ErrorText[];

/* Каждой таблице, с которой работает пользователь, должен соответствовать дескриптор типа THandle, получаемый от процедуры открытия таблицы. Все операции работы с таблицами используют этот дескриптор для ссылок на конкретную таблицу.*/

typedef struct Table * THandle;

typedef unsigned Bool; /* Булевский тип */

#define TRUE 1
#define FALSE 0

/* Следующий тип определяет возможные типы данных, хранимых в таблицах */

enum FieldType
{
  Text,     /* строка ( не более 256 символов) */
  Long,     /* целое длинное знаковое число */
  Logic
};

/* Эта структура задает описание одного поля таблицы */

struct FieldDef
{
  char name[MaxFieldNameLen]; /* имя данного поля */
  enum FieldType type; /* тип поля */
  unsigned len; /* длина поля в байтах */
};

/* Следующая структура определяет структуру таблицы и используется при создании новой таблицы. Информация об этой структуре хранится в табличном файле */

struct TableStruct
{
  unsigned numOfFields; /* число полей в таблице */
  struct FieldDef *fieldsDef; /* динамический массив,
  каждый элемент которого - описание поля таблицы */
};

/******************************************************/
/*  Ниже описываются прототипы функций для работы 	*/
/*  с таблицами. После каждого прототипа следует 		*/
/*  краткий комментарий							*/

enum Errors createTable(char *tableName,
			struct TableStruct *tableStruct);

/* Функция создает новую таблицу с заданным именем и структурой. При этом создается новый файл в текущей директории, в начальных областях файла сохраняется структура таблицы */

enum Errors deleteTable(char *tableName);

/* Функция удаляет таблицу с заданным именем */

enum Errors openTable(char *tableName, THandle *tableHandle);

/* Функция открывает таблицу с заданным именем для работы. По адресу tableHandle записывается дескриптор, который должен использоваться для ссылок на данную таблицу. При этом открывается файл таблицы. На основе заголовка файла таблицы, хранящего информацию о структуре таблицы, в оперативной памяти заполняется соответствующий элемент типа struct TableStruct. Создаются буферы для работы с текущей записью и для создания новой записи. Размер буферов определяется на основе структуры таблицы. */

enum Errors closeTable(THandle tableHandle);

/* Функция закрывает таблицу для использования. При этом освобождается место, занимаемое данной таблицей,и буферы, закрывается файл таблицы. */

enum Errors moveFirst(THandle tableHandle);

/* Функция устанавливает указатель файла на первую запись (если она есть) и считывает запись в буфер текущей записи. Если таблица пуста, то состояние буфера текущей записи не определено. При этом функции afterLast и beforeFirst выдают значение TRUE.*/

enum Errors moveLast(THandle tableHandle);

/* Функция устанавливает указатель файла на последнюю запись (если она есть) и считывает запись в буфер текущей записи.. Если таблица пуста, то состояние буфера текущей записи не определено. При этом функции afterLast и beforeFirst выдают значение TRUE.*/

enum Errors moveNext(THandle tableHandle);

/* Функция устанавливает указатель файла на следующую в файле запись (если она есть) и считывает запись в буфер текущей записи.. Если буфер уже находился на последней записи, то он переходит в состояние "после последней", в котором содержимое буфера не определено. При этом функция afterLast выдает значение TRUE.*/


enum Errors movePrevios(THandle tableHandle);

/* Функция устанавливает указатель файла на предыдущую запись (если она есть) и считывает запись в буфер текущей записи.. Если буфер уже находился на первой записи, то он переходит в состояние "перед первой", в котором содержимое буфера не определено. При этом функция beforeFirst выдает значение TRUE.*/

Bool beforeFirst(THandle tableHandle);

/* Функция выдает значение TRUE, если таблица пуста или если в состоянии "на первой записи" выполняется операция movePrevios, иначе выдается значение FALSE. */

Bool afterLast(THandle tableHandle);

/* Функция выдает значение TRUE, если таблица пуста или если в состоянии "на последней записи" выполняется операция moveNext, иначе выдается значение FALSE. */

enum Errors getText(THandle tableHandle, char *fieldName,char **pvalue);

/* Функция присваивает переменной pvalue указатель на строку - значение поля fieldName. */

enum Errors getLong(THandle tableHandle, char *fieldName,
		    long *pvalue);

/* Функция присваивает переменной pvalue целое число - значение поля fieldName. */

enum Errors startEdit(THandle tableHandle);

/* Функция используется перед началом редактирования текущей записи */

enum Errors putText(THandle tableHandle, char *fieldName,
		    char *value);

/* Функция присваивает полю fieldName - значение-строку */

enum Errors putLong(THandle tableHandle, char *fieldName,
		    long value);

/* Функция присваивает полю fieldName значение - целое число */

enum Errors finishEdit(THandle tableHandle);

/* Функция заканчивает редактирование текущей записи (в буфере). При этом производится запись обновленной записи в файл. */

enum Errors createNew(THandle tableHandle);

/* Функция обнуляет буфер новой записи, она используется перед заполнением буфера новой записи конкретными значениями */

/* Следующие две функции присваивают значения соответствующим полям в буфере новой записи. */

enum Errors putTextNew(THandle tableHandle, char 								*fieldName, char *value);
enum Errors putLongNew(THandle tableHandle,
					char * fieldName, long value);

enum Errors insertNew(THandle tableHandle);

/* Функция вставляет новую запись из буфера новой записи перед текущей записью (со сдвигом "хвоста").*/

enum Errors insertaNew(THandle tableHandle);

/* Функция вставляет новую запись из буфера новой записи в начало таблицы.*/

enum Errors insertzNew(THandle tableHandle);

/* Функция вставляет новую запись из буфера новой записи в конец таблицы.*/

enum Errors deleteRec(THandle tableHandle);

/* Функция удаляет текущую запись. При этом, если есть следующая запись, то она автоматически становится текущей, если нет, то появляется состояние "после последней". */

char *getErrorString(enum Errors code);

/* Функция по коду ошибки выдает ее представление в виде строки.*/

enum Errors getFieldLen(THandle tableHandle,char*fieldName,unsigned *plen);

/* Функция выдает длину поля таблицы в байтах. */

enum Errors getFieldType(THandle tableHandle,
			char *fieldName, enum FieldType *ptype);
/* Функция выдает тип поля таблицы. */

enum Errors getFieldsNum(THandle tableHandle,
								unsigned *pNum);
/* Функция выдает число полей в таблице. */

enum Errors getFieldName(THandle tableHandle,
			unsigned index, char **pFieldName);
/* Функция по номеру поля в таблице выдает его имя. Поля нумеруются с 1. */
#endif

