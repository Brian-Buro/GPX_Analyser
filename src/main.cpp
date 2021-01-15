#include <iostream>

#include "File.h"

int main() {
    std::cout << "Hello Main!" << "\n";

    File file("../sampleData/Walchensee.gpx"); 
    file.checkFile();

    return 0;
}