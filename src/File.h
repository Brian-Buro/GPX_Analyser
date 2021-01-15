#ifndef FILE_H
#define FILE_H

#include <string>

class File
{
public:
    File(std::string fileName) : _fileName(fileName) {};
    void checkFile();

private:
    std::string _fileName;
};

#endif
