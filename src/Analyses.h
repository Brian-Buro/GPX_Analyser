#ifndef ANALYSES_H
#define ANALYSES_H

#include <memory>
#include <ctime>
#include <vector>
#include <iostream>
#include <string>

template <typename dataType>
class AnalysisBase
{
public:
    AnalysisBase(const std::vector<std::time_t> &time, const std::vector<dataType> &data) : _time(time), _data(data){};
    dataType max();
    dataType min();
    float trackTimeSec();
    std::string trackTimeFormatted();

protected:
    void _calTrackTimeSec();
    float _trackTimeSec = -1;
    const std::vector<std::time_t> _time;
    const std::vector<dataType> _data;
    const float _minToSec = 60;
    const float _secToMin = 1 / _minToSec;
    const float _m_per_SecTokm_per_Hr = 3.6;
};

// I couldn't move AnalysisBase's member functions to the .cpp file. There were always errors.

template <typename dataType>
dataType AnalysisBase<dataType>::AnalysisBase::max()
{
    dataType maxValue = std::numeric_limits<dataType>::min();
    for (auto &value : _data)
        if (value > maxValue && value < 10000)
            maxValue = value;
    return maxValue;
}

template <typename dataType>
dataType AnalysisBase<dataType>::min()
{
    dataType minValue = std::numeric_limits<dataType>::max();
    for (auto &value : _data)
        if (value < minValue)
            minValue = value;
    return minValue;
}

template <typename dataType>
void AnalysisBase<dataType>::_calTrackTimeSec()
{
    _trackTimeSec = static_cast<float>(_time.back() - _time[0]);
}

template <typename dataType>
float AnalysisBase<dataType>::trackTimeSec()
{
    if (_trackTimeSec == -1)
        _calTrackTimeSec();

    return _trackTimeSec;
}

template <typename dataType>
std::string AnalysisBase<dataType>::trackTimeFormatted()
{
    int hr = trackTimeSec() / 3600;
    int min = (trackTimeSec() / 60) - (hr * 60);
    int sec = trackTimeSec() - (min * 60) - (hr * 3600);
    char formattedTime[] = "00:00:00";
    sprintf(formattedTime, "%2d:%2d:%2d", hr, min, sec);
    return std::string(formattedTime);
}

class SpeedAnalysis : public AnalysisBase<float>
{
public:
    SpeedAnalysis(const std::vector<std::time_t> &time, const std::vector<float> &speed) : AnalysisBase<float>(time, speed){};
    float stoppedTimeMin();
    float meanMovingSpeedKmPerH();

private:
    void _calStoppedTimeSec();
    void _calMeanMovingSpeedMeterProSec();
    double _stoppedTime = -1;          // Unit sec
    float _meanMovingSpeed = -1;       // Unit m/s
    const float _minSpeedMoving = 0.5; // Below this speed the GPS is considered to be stopped.
    const float _maxSpeed = 20;        // Speeds above this will be ignored. Unit m/s
};

class ElevationAnalysis : public AnalysisBase<int>
{
public:
    ElevationAnalysis(const std::vector<std::time_t> &time, const std::vector<int> &ele) : AnalysisBase<int>(time, ele){};
    int assentInMeters();
    int decentInMeters();

private:
    void _calVirticalTravel();
    int _assent = -1; // Unit: meters
    int _descent = 1; // Unit: meters
};

#endif