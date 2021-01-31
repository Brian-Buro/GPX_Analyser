#include <iostream>
#include <string>

#include "FileManager.h"
#include "Data.h"
#include "Analyses.h"

void printHelp()
{
    std::cout << "\nGPX Analyser Help\n";
    std::cout << "Analyse one file using an input argument:\n";
    std::cout << "\tLunch with arguments: ./GPX_Analyser -a ../sampleData/Walchensee.gpx\n";
    std::cout << "Or analyse multiple files using commands:\n";
    std::cout << "\tLunch without arguments: ./GPX_Analyser\n";
    std::cout << "\tCommands:\n";
    std::cout << "\tAnalyse a file: a\n";
    std::cout << "\tQuit: q\n";
    std::cout << "\tHelp: h\n";
    std::cout << "\n";
}
void runGpxAnalysis(const std::string &fName)
{
    std::cout << "Running... \n";
    FileManager fileMan;
    fileMan.addFile(fName);
    fileMan.loadFile(0);
    fileMan.printAnalysis(0, 0);
}

void commands()
{
    std::string cmd = "";
    std::string fName = "";
    while (1)
    {
        std::cout << "Enter cmd (h for help): \n";
        std::cin >> cmd;
        if (cmd == "q")
            return;
        else if (cmd == "h")
            printHelp();
        else if (cmd == "a")
        {
            std::cout << "Enter file path (without spaces): \n";
            std::cin >> fName;
            runGpxAnalysis(fName);
        }
        fName = "";
    }
}

int main(int argc, char **argv)
{

    std::cout << "\n** GPX Analyser **\n";
    if (argc == 3 && std::strcmp(argv[1], "-a") == 0)
    {
        runGpxAnalysis(argv[2]);
    }
    else if (argc == 1)
    {
        commands();
    }
    else
    {
        printHelp();
    }

    return 0;
}