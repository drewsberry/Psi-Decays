#include "Main.h"

// We want to use Example
#include "Program.h"

int main(int argc, char **argv)
{
    std::cout << "Use switch \"-p\" or \"--persistent\" for app persistence." 
        << std::endl;
    std::cout << std::endl;
  
////////////// Allows it to make plots... but run with -b if you don't want them on screen!!!
    TApplication *App = new TApplication("App",&argc,argv); 
    std::cout << "App created." << std::endl;
  
////////////// Create an instance of class "Example" called "Exy"
    Program *Prog = new Program;
    std::cout << "Prog created." << std::endl;
  
///////////// Runs the actual code
    std::cout << "Executing code..." << std::endl;
    Prog -> Fit();
    Prog -> Boost();
  
///////////// If switch used, run app
///////////// Any pointer you create with "new" you must delete
    delete Prog;
    std::cout << "Prog deleted." << std::endl;
  
    // Add the option to run root persistently
    std::string persistentFlag1 = "--persistent";
    std::string persistentFlag2 = "-p";
  
    if (argv[1] != NULL)
    {
        if ((argv[1] == persistentFlag1) || (argv[1] == persistentFlag2))
        {
            std::cout << std::endl << "Running app persistently..." << std::endl
                << "Press CTRL-C to exit..." << std::endl;
            App -> Run();
        }
    }
  
    delete App;
    std::cout << "App deleted. " << std::endl ;
  
    return true; // exits the function
}

