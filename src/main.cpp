#include <iostream>

#include "FileManager.h"
#include "Data.h"

int main() {
/*
    FileManager fileMan;
    fileMan.addFile("../sampleData/Walchensee.gpx"); 
    fileMan.addFile("../sampleData/Walchensee2.gpx"); 
*/
    Data d;
    std::string a("../sampleData/Walchensee.gpx");
    d.readFromFile(a);

    return 0;
}