#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <memory>
#include <string>
#include "File.h"
#include "Data.h"
#include "Analyses.h"

class FileManager
{
public:
    void addFile(std::string fileName);
    void loadFile(int filePosition);
    void printAnalysis(int filePosition, int trkPos);

private:
    // Vectors to allow the program to handle multiple files in the future.
    // These vectors will be the same length. 1 data class per file.
    std::vector<std::unique_ptr<File>> _files;
    std::vector<std::unique_ptr<Data>> _data;
};

#endif