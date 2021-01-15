#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <memory>
#include <string>
#include "File.h"

class FileManager
{
public:
    void addFile(std::string fileName);

private:
    std::vector<std::unique_ptr<File>> _files;
    // DataVector
};

#endif