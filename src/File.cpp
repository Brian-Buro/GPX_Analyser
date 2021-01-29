#include <iostream>
#include "File.h"

bool File::isOK()
{
    fs::file_status status = fs::status(_path.string());
    if (!fs::exists(status))
    {
        std::cout << _path << " does not exist.\n";
        return false;
    }
    if (_path.extension() != ".gpx")
    {
        std::cout << _path << " File extension is not gpx.\n";
        return false;
    }
    if (fs::is_directory(status))
    {
        std::cout << _path << " Path is a directory, expected a file.\n";
        return false;
    }
    return true;
}

void File::printPath()
{
    std::cout << "Path: " << _path << "\n";
}

std::string File::filePath()
{
    return _path.string();
}

std::string File::fileName()
{
    return _path.filename();
}

