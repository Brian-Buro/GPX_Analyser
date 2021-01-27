#include <iostream>
//#include <iomanip>

#include "FileManager.h"
#include "Data.h"
#include "Analyses.h"

int main() {
/*
    FileManager fileMan;
    fileMan.addFile("../sampleData/Walchensee.gpx"); 
    fileMan.addFile("../sampleData/Walchensee2.gpx"); 
*/
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


    std::vector<std::time_t> t{1, 2, 3, 4, 5};
    std::vector<float> speed{0.1, 1.2, 2.5, 3.3, 2};
    std::vector<int> ele{-1, 0, 20, 25, -20};

    AnalysisBase<float> aBase;
    std::cout << aBase.s;
    AnalysisBase<float> anotherBase(t, speed);
    std::cout << "Max: " << anotherBase.max() << "\n";
    std::cout << "Min: " << anotherBase.min() << "\n";

    std::cout << "\nSpeedAnalysis...\n";
    SpeedAnalysis sSpeedAnaly;
    std::cout << sSpeedAnaly.s;
    std::cout << sSpeedAnaly.ss;

    SpeedAnalysis anotherSpeedAnaly(t, speed);
    std::cout << anotherSpeedAnaly.s;
    std::cout << "Max: " << anotherSpeedAnaly.max() << "\n";
    std::cout << "Min: " << anotherSpeedAnaly.min() << "\n";

    std::cout << "\nElevationAnalysis...\n";
    ElevationAnalysis eAnalyis(t, ele);
    std::cout << "Max: " << eAnalyis.max() << "\n";
    std::cout << "min: " << eAnalyis.min() << "\n";


    std::cout << "\n\nIt's all about the base...\n";
    Base b;
    std::cout << b.basePar;
    Derived d;
    std::cout << d.derivedPar;

    return 0;
}