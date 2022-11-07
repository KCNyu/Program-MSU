//  Replace an original function with a custom function defined in the tool using
//  probes.  The replacement function has a different signature from that of the
//  original replaced function.

#include "pin.H"
#include <iostream>
#include <openssl/blowfish.h>
#include <fstream>
#define BF_SET_KEY "BF_set_key"

using namespace std;


// This is the replacement routine.
//
VOID NewBF(CONTEXT * context, AFUNPTR orgFuncptr, BF_KEY* arg0, int arg1, const unsigned char* arg2)
{
    // Call the relocated entry point of the original (replaced) routine.
    void * res;

    cout << arg1 << endl;
    cout << "original key:\n" << arg2 << endl;

    fstream readFile("decrypt.key", ios::in | ios::binary);
    char key[arg1+1];
    readFile.read(key, arg1);
    cout << "replaced by key from decrpyt.key:\n" << key << endl; 

    PIN_CallApplicationFunction(context, PIN_ThreadId(),
            CALLINGSTD_DEFAULT, orgFuncptr, NULL, PIN_PARG(int), &res, PIN_PARG(BF_KEY*), arg0, PIN_PARG(int), arg1, PIN_PARG(const unsigned char*), key, PIN_PARG_END());
}

// Pin calls this function every time a new img is loaded.
// It is best to do probe replacement when the image is loaded,
// because only one thread knows about the image at this time.
//
VOID ImageLoad(IMG img, VOID* v)
{
    // See if malloc() is present in the image.  If so, replace it.
    //
    RTN rtn = RTN_FindByName(img, BF_SET_KEY);

    if (RTN_Valid(rtn))
    {
        PROTO proto_bf_set_key = PROTO_Allocate(PIN_PARG(void), CALLINGSTD_DEFAULT, BF_SET_KEY, PIN_PARG(BF_KEY*), PIN_PARG(int), PIN_PARG(const unsigned char*), PIN_PARG_END());

        // Replace the application routine with the replacement function.
        // Additional arguments have been added to the replacement routine.
        //
        RTN_ReplaceSignature(rtn, AFUNPTR(NewBF), IARG_PROTOTYPE, proto_bf_set_key,
                IARG_CONTEXT,
                IARG_ORIG_FUNCPTR,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
                IARG_END);

        // Free the function prototype.
        //
        PROTO_Free(proto_bf_set_key);
    }
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    cerr << "This tool demonstrates how to replace an original" << endl;
    cerr << " function with a custom function defined in the tool " << endl;
    cerr << " using probes.  The replacement function has a different " << endl;
    cerr << " signature from that of the original replaced function." << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

/* ===================================================================== */
/* Main: Initialize and start Pin in Probe mode.                         */
/* ===================================================================== */

int main(INT32 argc, CHAR* argv[])
{
    // Initialize symbol processing
    //
    PIN_InitSymbols();

    // Initialize pin
    //
    if (PIN_Init(argc, argv)) return Usage();

    // Register ImageLoad to be called when an image is loaded
    //
    IMG_AddInstrumentFunction(ImageLoad, 0);

    // Start the program in probe mode, never returns
    //
    PIN_StartProgram();

    return 0;
}
