#include "pin.H"
#include <iostream>
#include <fstream>

#define BF_SET_KEY "BF_set_key"

/* ===================================================================== */
/* Global Variables */
/* ===================================================================== */

std::ofstream TraceFile;

/* ===================================================================== */
/* Commandline Switches */
/* ===================================================================== */

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "encrypt.out", "specify trace file name");

/* ===================================================================== */
/* Save key to encypt.key */
/* ===================================================================== */

VOID save(ADDRINT &len, const CHAR* &data)
{
    ofstream outFile("encrypt.key", ios::out | ios::binary);
    outFile.write(data, len);
}
/* ===================================================================== */
/* Analysis routines                                                     */
/* ===================================================================== */

VOID bfArg(CHAR * name, ADDRINT len, const CHAR* data)
{
    TraceFile << name << "(" << len << ", " << data << ")" << endl; 
    save(len, data);
}

/* ===================================================================== */
/* Instrumentation routines                                              */
/* ===================================================================== */
   
VOID Image(IMG img, VOID *v)
{
    RTN bfRtn = RTN_FindByName(img, BF_SET_KEY);
    if (RTN_Valid(bfRtn))
    {
        RTN_Open(bfRtn);

        RTN_InsertCall(bfRtn, IPOINT_BEFORE, (AFUNPTR)bfArg,
                       IARG_ADDRINT, BF_SET_KEY,
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
                       IARG_END);

        RTN_Close(bfRtn);
    }
}

/* ===================================================================== */

VOID Fini(INT32 code, VOID *v)
{
    TraceFile.close();
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */
   
INT32 Usage()
{
    cerr << "This tool produces a trace of calls to malloc." << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char *argv[])
{
    // Initialize pin & symbol manager
    PIN_InitSymbols();
    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }
    
    // Write to a file since cout and cerr maybe closed by the application
    TraceFile.open(KnobOutputFile.Value().c_str());
    //TraceFile << hex;
    //TraceFile.setf(ios::showbase);
    
    // Register Image to be called to instrument functions.
    IMG_AddInstrumentFunction(Image, 0);
    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();
    
    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
