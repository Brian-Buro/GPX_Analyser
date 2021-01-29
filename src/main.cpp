#include <iostream>
#include <string>

#include "FileManager.h"
#include "Data.h"
#include "Analyses.h"

void printHelp()
{
    std::cout << "\nGPX Analysier Help\n\n";
    std::cout << "Commands:\n";
    std::cout << "Load file: load <..\\path\\to\\file.gpx>\n";
    std::cout << "Analyse a loaded file: analyse file_<number>_trk<number>\n";
    std::cout << "List loaded files: list\n";
    std::cout << "Help: h\n";
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
        std::cout << "Enter cmd: \n";
        std::cin >> cmd;
        if (cmd == "q")
            return;
        else if (cmd == "h")
            printHelp();
        else if (cmd == "f")
        {
            std::cout << "Enter file path (without spaces): \n";
            std::cin >> fName;
            runGpxAnalysis(fName);
        }
        fName = "";
    }
}

int main(int argc, const char **argv)
{

    std::cout << "\nGPX Analysier\n\n";
    if (argc == 3 && std::string_view{argv[1]} == "-f")
    {
        //fileMan.addFile("../sampleData/Walchensee.gpx");
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