#include <iostream>
#include <filesystem>
#include "File.h"

void File::checkFile()
{
    if (std::filesystem::exists(_fileName))
    {
        std::cout << _fileName << " exists.\n";
    } else
    {
        std::cout << _fileName << " does not exist.\n";
    }
}