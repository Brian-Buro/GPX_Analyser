#ifndef FILE_H
#define FILE_H

#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class File
{
public:
    File(std::string fileName) : _path(fileName){};
    bool isOK();
    void printPath();
    std::string filePath();
    std::string fileName();

private:
    fs::path _path;
};

#endif
