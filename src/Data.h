#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <utility>
#include <regex>
#include <cmath>
#include <ctime>

struct Trk // Container for all Track information
{
    std::vector<std::time_t> time;                // Number of sec since the epoch
    std::vector<int> ele;                         // m above sea level
    std::vector<std::pair<double, double>> trkpt; // lon, lat
    std::vector<float> speed;                     // m/s
    double distanceTraveled = 0;                  // km
    std::string name = "";                        // Track name
};

class Data
{
public:
    void readFromFile(const std::string &fileName);
    void calculateSpeedAndDistanceTracks();
    std::shared_ptr<Trk> getTrackByIndex(int trkIdx);

private:
    void _calculateSpeedAndDistanceTrk(std::shared_ptr<Trk> &trk);
    std::vector<std::shared_ptr<Trk>> _tracks;  // A GPX file can contain multiple tracks, therefor a vector is used.
};

namespace GpxUtilities // Constants and functions needed to process the gpx data.
{
    // Source: https://en.wikipedia.org/wiki/World_Geodetic_System#WGS84
    const double wgs84Major{6378137};
    const double wgs84Minor{6356752.314245};
    const double e2 = 1 - (pow(wgs84Minor, 2) / pow(wgs84Major, 2));

    std::vector<double> convertCoordinates(double lat, double lon, int ele);
    double distance(const std::vector<double> &point1xyz, const std::vector<double> &point2xyz);
    double speed(std::pair<double, double> timePosPoint1, std::pair<double, double> timePosPoint2);
}; // namespace GpxUtilities

class GpxParser
{
public:
    GpxParser(const std::string &fileName);
    ~GpxParser();
    void parseFile(); // Later pass the file object
    void getTracks(std::vector<std::shared_ptr<Trk>> &tracks);
    static std::time_t parseTime(const char *time);

private:
    // XML Tags used in the GPX file.
    const std::string trkTagBegin = "<trk>";
    const std::string trkTagEnd = "</trk>";
    const std::string nameTagBegin = "<name>";
    const std::string nameTagEnd = "</name>";
    const std::string trksegTagBegin = "<trkseg>";
    const std::string trksegTagEnd = "</trkseg>";
    const std::string trkptBegin = "<trkpt";
    const std::string eleTagBegin = "<ele>";
    const std::string eleTagEnd = "</ele>";
    const std::string timeBegin = "<time>";
    const std::string timeEnd = "</time>";

    std::vector<std::shared_ptr<Trk>> _tracks;
    std::ifstream _fileStream;
    std::string _line;
    std::string _tag;
    std::regex _regexExpression;

    void _readTrack();
    void _readTrackSegment(std::shared_ptr<Trk> &trk);
    void _extractName(std::shared_ptr<Trk> &trk);
    void _extractTrkpt(std::shared_ptr<Trk> &trk);
    void _extractEle(std::shared_ptr<Trk> &trk);
    void _extractTime(std::shared_ptr<Trk> &trk);
};

#endif