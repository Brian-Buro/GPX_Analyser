#include "Data.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

/*** GpxParser Parser ***/
void GpxParser::_readTrack()
{
    // A GPX file can have multipule tracks.
    std::shared_ptr<Trk> trk = std::make_shared<Trk>(Trk());

    // Each element can only be present once. When it has been found
    // the string no longer needs to be compared.
    bool nameEvaluated{false};

    while (std::getline(_fileStream, _line))
    {
        if (!nameEvaluated && _line.find(nameTagBegin) != std::string::npos)
        {
            _extractName(trk);
            nameEvaluated = true;
        }
        if (_line.find(trksegTagBegin) != std::string::npos)
        {
            _readTrackSegment(trk);
        }
        if (_line.find(trkTagEnd) != std::string::npos)
        {
            _tracks.emplace_back(trk);
            return;
        }
    }
}

void GpxParser::_extractName(std::shared_ptr<Trk> &trk)
{
    std::smatch m;
    _regexExpression = nameTagBegin + "(.+)" + nameTagEnd;
    if (std::regex_search(_line, m, _regexExpression))
        trk->name = m[1].str();
}

void GpxParser::_readTrackSegment(std::shared_ptr<Trk> &trk)
{
    while (std::getline(_fileStream, _line))
    {
        if (_line.find(trkptBegin) != std::string::npos)
            _extractTrkpt(trk);
        if (_line.find(eleTagBegin) != std::string::npos)
            _extractEle(trk);
        if (_line.find(timeBegin) != std::string::npos)
            _extractTime(trk);
        if (_line.find(trksegTagEnd) != std::string::npos)
            return;
    }
}

void GpxParser::_extractTrkpt(std::shared_ptr<Trk> &trk)
{
    std::pair<double, double> trkpt;
    std::smatch m;
    _regexExpression = "lon=\"([\\d\\.]+)\"";

    if (std::regex_search(_line, m, _regexExpression))
        trkpt.first = std::stod(m[1].str());

    _regexExpression = "lat=\"([\\d\\.]+)\"";
    if (std::regex_search(_line, m, _regexExpression))
        trkpt.second = std::stod(m[1].str());

    trk->trkpt.push_back(trkpt);
}

void GpxParser::_extractEle(std::shared_ptr<Trk> &trk)
{
    int ele;
    std::smatch m;
    _regexExpression = ">([\\.\\d]+)<";
    if (std::regex_search(_line, m, _regexExpression))
        ele = std::stoi(m[1].str());
    trk->ele.push_back(ele);
}

void GpxParser::_extractTime(std::shared_ptr<Trk> &trk)
{
    std::time_t time;
    std::smatch m;
    _regexExpression = ">(.+)<";
    if (std::regex_search(_line, m, _regexExpression))
    {
        time = parseTime(m[1].str().c_str());
    }
    trk->time.push_back(time);
}

/** Main parser function **/
void GpxParser::parseFile()
{
    while (std::getline(_fileStream, _line))
    {
        std::istringstream lineStream(_line);
        lineStream >> _tag;
        if (_tag.compare(trkTagBegin) == 0)
        {
            _readTrack();
            std::getline(_fileStream, _line);
            break;
        }
    }
}

GpxParser::GpxParser(const std::string &fileName)
{
    _fileStream = std::ifstream(fileName);
    if (!_fileStream.is_open())
        throw std::runtime_error{"File could not be opened."};
}

GpxParser::~GpxParser()
{
    if (_fileStream.is_open())
        _fileStream.close();
}

void GpxParser::getTracks(std::vector<std::shared_ptr<Trk>> &tracks)
{
    tracks = _tracks;
}

std::time_t GpxParser::parseTime(const char *time)
{
    /* 2020-04-12T12:52:18Z */
    struct tm timeStruct
    {
        0
    };
    int y, mon, d, h, min, s;
    sscanf(time, "%4d-%2d-%2dT%2d:%2d:%2dZ", &y, &mon, &d, &h, &min, &s);
    timeStruct.tm_year = y - 1900;
    timeStruct.tm_mon = mon - 1;
    timeStruct.tm_mday = d;
    timeStruct.tm_hour = h;
    timeStruct.tm_min = min;
    timeStruct.tm_sec = s;
    timeStruct.tm_zone = "GMT";
    std::time_t t = std::mktime(&timeStruct);
    return t;
}

/*** GpxUtilities ***/

std::vector<double> GpxUtilities::convertCoordinates(double lat, double lon, int ele)
{
    // Source: https://en.wikipedia.org/wiki/Geographic_coordinate_conversion
    lat = lat * M_PI / 180;
    lon = lon * M_PI / 180;
    const double N = wgs84Major / sqrt(1 - e2 * pow(sin(abs(lat)), 2));
    double X = (N + ele) * cos(lat) * cos(lon);
    double Y = (N + ele) * cos(lat) * sin(lon);
    double Z = ((N * pow(wgs84Minor, 2) / pow(wgs84Major, 2)) + ele) * sin(lat);
    return std::vector<double>{X, Y, Z};
}

double GpxUtilities::distance(const std::vector<double> &point1xyz, const std::vector<double> &point2xyz)
{
    auto deltaPoints = [](double p1, double p2) { return pow(p2 - p1, 2); };
    double delta = 0;
    for (int axis = 0; axis < 3; axis++)
        delta += deltaPoints(point1xyz[axis], point2xyz[axis]);
    return sqrt(delta);
}

double GpxUtilities::speed(std::pair<double, double> timePosPoint1, std::pair<double, double> timePosPoint2)
{
    double d = 0.0;
    return d;
}

/*** Data ***/

/* Read file, parse and add to _tracks */
void Data::readFromFile(const std::string &fileName)
{
    GpxParser gpx(fileName);
    gpx.parseFile();
    gpx.getTracks(_tracks);
}

void Data::_calculateSpeedAndDistanceTrk(std::shared_ptr<Trk> &trk)
{
    std::vector<double> pointxyzPre(3);
    std::vector<double> pointxyz(3);
    double delta_s = 0;
    std::time_t t;
    std::time_t tPre = trk->time[0];
    int delta_t = 0;

    pointxyzPre = GpxUtilities::convertCoordinates(trk->trkpt[0].second, trk->trkpt[0].first, trk->ele[0]);
    // trk->speed.push_back(0.0);
    for (size_t idx = 1; idx < trk->trkpt.size(); idx++)
    {
        pointxyz = GpxUtilities::convertCoordinates(trk->trkpt[idx].second, trk->trkpt[idx].first, trk->ele[idx]);
        delta_s = GpxUtilities::distance(pointxyzPre, pointxyz);
        t = trk->time[idx];
        delta_t = t - tPre;

        trk->speed.push_back(delta_s / delta_t * 3.6);
        trk->distanceTraveled += (delta_s / 1000);

        pointxyzPre = pointxyz;
        tPre = t;
    }
    trk->speed.push_back(delta_s / delta_t * 3.6); // Done so that all vectors have the same length
}

void Data::calculateSpeedAndDistanceTracks()
{
    // The speed and distance will be calculated for all tracks present
    for (size_t trkIdx = 0; trkIdx < _tracks.size(); trkIdx++)
    {
        _calculateSpeedAndDistanceTrk(_tracks[trkIdx]);
    }
}

std::shared_ptr<Trk> Data::getTrackByIndex(int trkIdx)
{
    return _tracks[trkIdx];
}