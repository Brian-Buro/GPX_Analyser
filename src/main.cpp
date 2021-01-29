#include <iostream>
//#include <iomanip>

#include "FileManager.h"
#include "Data.h"
#include "Analyses.h"

int main()
{

    FileManager fileMan;
    fileMan.addFile("../sampleData/Walchensee.gpx"); 
    fileMan.addFile("../sampleData/Walchensee2.gpx"); 
    fileMan.loadFile(0);
    fileMan.printAnalysis(0,0);

/*    
    Data d;
    std::string a("../sampleData/Walchensee.gpx");
    d.readFromFile(a);
    d.calculateSpeedAndDistanceTracks();
*/
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
/*
    std::vector<std::time_t> t{1, 2, 3, 4, 5};
    std::vector<float> speed{10, 10, 3, 20, 20};
    std::vector<int> ele{-10, 1, -5, -5, 0};

    std::cout << "\nBaseAnalysis...\n";
    AnalysisBase<float> anotherBase(t, speed);
    std::cout << "Max: " << anotherBase.max() << "\n";
    std::cout << "Min: " << anotherBase.min() << "\n";

    std::cout << "\nSpeedAnalysis...\n";
    SpeedAnalysis aSpeedAnalysis(t, speed);
    std::cout << "Max: " << aSpeedAnalysis.max() << "\n";
    std::cout << "Min: " << aSpeedAnalysis.min() << "\n";
    std::cout << "Stopped Time: " << aSpeedAnalysis.stoppedTimeMin() << " min\n";
    std::cout << "Moving avg speed: " << aSpeedAnalysis.meanMovingSpeedKmPerH() << " km/hr\n";

    std::cout << "\nElevationAnalysis...\n";
    ElevationAnalysis anEleAnalysis(t, ele);
    std::cout << "Max: " << anEleAnalysis.max() << "\n";
    std::cout << "min: " << anEleAnalysis.min() << "\n";
    std::cout << "Climb: " << anEleAnalysis.assentInMeters() << "\n";
    std::cout << "Decs: " << anEleAnalysis.decentInMeters() << "\n";
*/
    return 0;
}