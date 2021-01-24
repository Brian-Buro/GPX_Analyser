#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <utility>
#include <regex>

struct Trk
{
    std::vector<std::string> time;
    std::vector<float> ele;
    std::vector<std::pair<double, double>> trkpt;
    std::vector<float> speed;
    std::string name = "";
};

class Data
{
public:
    void readFromFile(std::string &fileName); // Later pass the file object
    // Speed cal

private:
    std::vector<std::shared_ptr<Trk>> _tracks;
};

class GpxParser
{
public:
    GpxParser(std::string &fileName);
    ~GpxParser();
    void parseFile(); // Later pass the file object
    void getTracks(std::vector<std::shared_ptr<Trk>> &tracks);

private:
    // Constants
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

    // Variables
    std::vector<std::shared_ptr<Trk>> _tracks;
    std::ifstream _fileStream;
    std::string _line;
    std::string _tag;
    std::regex _regexExpression;

    // Functions
    void _readTrack();
    void _readTrackSegment(std::shared_ptr<Trk> &trk);
    void _extractName(std::shared_ptr<Trk> &trk);
    void _extractTrkpt(std::shared_ptr<Trk> &trk);
    void _extractEle(std::shared_ptr<Trk> &trk);
    void _extractTime(std::shared_ptr<Trk> &trk);
};

#endif