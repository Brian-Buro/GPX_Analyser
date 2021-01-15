#include <iostream>

#include "FileManager.h"

int main() {

    FileManager fileMan;
    fileMan.addFile("../sampleData/Walchensee.gpx"); 
    fileMan.addFile("../sampleData/Walchensee2.gpx"); 

    return 0;
}