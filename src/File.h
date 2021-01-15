#ifndef FILE_H
#define FILE_H

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class File
{
public:
    File(std::string fileName) : _path(fileName){};
    bool isOK();
    void printPath();

private:
    fs::path _path;
};

#endif
