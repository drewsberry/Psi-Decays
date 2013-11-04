#include "../include/Main.h"
#include "../include/Program.h"
#include "../include/LHCbStyle.h"
using namespace std;

bool flagCheck(string, int, char, bool *);
void printHelp(bool);

bool flagCheck(string flag, int argc, char *argv[], bool *argbool)
{
    int i = 0;
    for(i = 0; i < argc; i++) {
        if(argv[i] == flag) {
            argbool[i] = true;
            return true;
        }
    } 
    return false;
}

void printHelp(bool options)
{
    if(options) {
        cout << "Options: " << endl;
        cout << "\t-h : print root usage" << endl;
        cout << "\t-b : run in batch mode without graphics" << endl << endl;
        cout << "\t--help       : print root usage" << endl;
        cout << "\t--persist    : run persistently, meaning graphics remain; exit with CTRL-C" << endl;
        cout << "\t--lhcb-style : use the standard LHCb presentation standards" << endl << endl;
    }
}

int main(int argc, char *argv[])
{
    int i = 0;
    bool argbool[argc];
    argbool[0] = true;
    for(i = 1; i < argc; i++) {
        argbool[i] = false;
    }

    bool batch = flagCheck("-b", argc, argv, argbool);
    bool lhcbStyle = flagCheck("--lhcb-style", argc, argv, argbool);
    bool persist = flagCheck("--persist", argc, argv, argbool);
    bool options = flagCheck("--options", argc, argv, argbool);

    if(argc - 1 > batch + lhcbStyle + persist + options) {
        for(i = 0; i < argc; i++) {
            if(argbool[i] == false) {
                cout << "Unknown option: " << argv[i] << endl;
            }
        }
        cout << endl;
        printHelp(true);
        return 1;
    }

    printHelp(options);
  
    if(lhcbStyle) {
        LHCbStyle();
    }
  
////////////// Allows it to make plots... but run with -b if you don't want them on screen!!!
    TApplication *App = new TApplication("App",&argc,argv); 
    cout << "App created." << endl;
  
////////////// Create an instance of class "Program" called "Prog"
    Program *Prog = new Program;
    cout << "Prog created." << endl;
  
///////////// Runs the actual code
    cout << "Executing code..." << endl;
    Prog->Setup();
    Prog->Fit();
    Prog->Boost();
  
///////////// If switch used, run app
///////////// Any pointer you create with "new" you must delete
    delete Prog;
    cout << "Prog deleted." << endl;

    if(persist) {
        cout << endl << "Running app persistently... " << endl
            << "Press CTRL-C to exit." << endl;
        App->Run();
    }

    delete App;
    cout << "App deleted." << endl ;
  
    return 0;
}

