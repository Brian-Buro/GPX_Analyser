#include "FileManager.h"

void FileManager::addFile(std::string fileName)
{
    File newFile(fileName);
    if (newFile.isOK())
        _files.push_back(std::move(std::make_unique<File>(newFile)));
}
