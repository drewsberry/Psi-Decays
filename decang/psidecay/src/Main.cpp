#include "../include/Main.h"
#include "../include/Program.h"
#include "../include/LHCbStyle.h"
using namespace std;

static int batch = 0, lhcb_style = 0, persist = 0;

void usage()
{
    cout << "Usage: Main [OPTION]...\n" << endl;
    cout << "Options: \n"
            "  -h, --help       : print this help and exit\n"
            "  -b, --batch      : run in batch mode without graphics\n"
            "  -p, --persist    : run persistently, meaning graphics remain; exit with CTRL-C\n"
            "  -s, --lhcb-style : use the standard LHCb presentation standards" << endl;
}

int main(int argc, char *argv[])
{
    int flag;

    while(1) {
        static struct option long_options[] = {
        {"batch",      no_argument, &batch,      true},
        {"lhcb-style", no_argument, &lhcb_style, true},
        {"persist",    no_argument, &persist,    true},
        {"help",       no_argument, 0, 'h'},
        {0, 0, 0, 0}
        };

        // This is where getopt_long stores the option index.
        int option_index = 0;

        flag = getopt_long(argc, argv, "bph",
                           long_options, &option_index);

        // Detect the end of the options
        if(flag == -1)
            break;

        switch(flag) {
            case 'b':
                break;
            case 'p':
                break;
            case 'h':
                usage();
                return 0;
            case '?':
                printf("Try `%s --help' for more information.\n",argv[0]);
                return 1;
            default:
                usage();
                abort();
        }
    }
  
    if(lhcb_style) {
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

