#include "Data.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

/** Helper functions for the parser **/
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
    float ele;
    std::smatch m;
    _regexExpression = ">([\\.\\d]+)<";
    if (std::regex_search(_line, m, _regexExpression))
        ele = std::stof(m[1].str());
    trk->ele.push_back(ele);
}

void GpxParser::_extractTime(std::shared_ptr<Trk> &trk)
{
    std::string time;
    std::smatch m;
    _regexExpression = ">(.+)<";
    if (std::regex_search(_line, m, _regexExpression))
    {
        time = m[1].str();
    }
    trk->time.push_back(time);
}

/** Main parser funtion **/
void GpxParser::parseFile()
{
    while (std::getline(_fileStream, _line))
    {
        std::istringstream lineStream(_line);
        lineStream >> _tag;
        std::cout << _line << "\n";
        if (_tag.compare(trkTagBegin) == 0)
        {
            _readTrack();
            std::getline(_fileStream, _line);
            std::cout << "in parseFile: " << _line << "\n";
            break;
        }
    }
}

GpxParser::GpxParser(std::string &fileName)
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

/* Read file, parse and add to _tracks */
void Data::readFromFile(std::string &fileName)
{
    GpxParser gpx(fileName);
    gpx.parseFile();
    gpx.getTracks(_tracks);
}
