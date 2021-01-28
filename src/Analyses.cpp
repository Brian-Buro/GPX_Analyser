#include <limits>
#include "Analyses.h"

float SpeedAnalysis::stoppedTimeMin()
{
    if (_stoppedTime == -1)
        _calStoppedTimeSec();
    return _stoppedTime * _secToMin;
}

void SpeedAnalysis::_calStoppedTimeSec()
{
    _stoppedTime = 0;
    for (size_t idx = 0; idx < _data.size() - 1; idx++)
    {
        if (_data[idx] < _minSpeedMoving)
            _stoppedTime += static_cast<double>(_time[idx + 1] - _time[idx]);
    }
}

float SpeedAnalysis::meanMovingSpeedKmPerH()
{
    if (_meanMovingSpeed == -1)
        _calMeanMovingSpeedMeterProSec();
    return _meanMovingSpeed * _m_per_SecTokm_per_Hr;
}

void SpeedAnalysis::_calMeanMovingSpeedMeterProSec()
{
    /* The average speed must be calculated with a 
    weighted average, because not every time step 
    is equal. Speed will be weighted with time.*/

    _meanMovingSpeed = 0;
    double timeStep = 0;
    double totalTimeMoving = 0;
    double weightedSpeedMoving = 0;
    for (size_t idx = 0; idx < _data.size() - 1; idx++)
    {
        if (_data[idx] >= _minSpeedMoving)
        {
            timeStep = static_cast<double>(_time[idx + 1] - _time[idx]);
            totalTimeMoving += timeStep;
            weightedSpeedMoving += (timeStep * _data[idx]);
        }
    }
    _meanMovingSpeed = totalTimeMoving == 0 ? 0 : weightedSpeedMoving / totalTimeMoving;
}

int ElevationAnalysis::assentInMeters()
{
    if (_assent == -1)
        _calVirticalTravel();
    return _assent;
}

int ElevationAnalysis::decentInMeters()
{
    if (_descent == 1)
        _calVirticalTravel();
    return _descent;
}

void ElevationAnalysis::_calVirticalTravel()
{
    _assent = 0;
    _descent = 0;

    for (size_t idx = 1; idx < _data.size(); idx++)
    {
        if (_data[idx - 1] < _data[idx])
            _assent += std::abs(_data[idx - 1] - _data[idx]);
        else if (_data[idx - 1] > _data[idx])
            _descent += -std::abs(_data[idx - 1] - _data[idx]);
    }
}