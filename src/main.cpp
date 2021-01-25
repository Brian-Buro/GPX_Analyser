#include <iostream>
//#include <iomanip>

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
    d.calculateSpeedAndDistanceTracks();

/*
    char dateTime[] = "2020-04-12T12:52:18Z";
    std::time_t t = GpxParser::parseTime(dateTime);
    std::cout << "The time is: " << std::put_time(std::gmtime(&t), "%c %Z") << "\n";
*/
/*
    std::vector<double> p1 = GpxUtilities::convertCoordinates(double(47.748540282), double(11.516492721), 701);
    std::vector<double> p2 = GpxUtilities::convertCoordinates(double(47.626385123), double(11.355071981), 812);
    double dist = GpxUtilities::distance(p1, p2);
    auto printP = [](std::vector<double> &p){std::cout << "P1: X " << p[0] << " Y " << p[1] << " Z " << p[2] << "\n";};
    printP(p1);
    printP(p2);
    std::cout << "dist: " << dist << "\n";
*/


    return 0;
}