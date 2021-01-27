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
    AnalysisBase() { std::cout << "Default ctor in base!\n"; }

    AnalysisBase(std::vector<std::time_t> time, std::vector<dataType> data) : _time(time), _data(data)
    {
        std::cout << "Ctor in base!\n";
    };
    dataType max();
    dataType min();
    const std::string s{"Im alive!\n"};

private:
    std::vector<std::time_t> _time;
    std::vector<dataType> _data;
};

template <typename dataType>
dataType AnalysisBase<dataType>::AnalysisBase::max()
{
    dataType maxValue = std::numeric_limits<dataType>::min();
    for (auto &value : _data)
        if (value > maxValue)
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

class SpeedAnalysis : public AnalysisBase<float>
{
public:
    SpeedAnalysis() { std::cout << "SpeedAnalysis c'tor\n"; };
    SpeedAnalysis(std::vector<std::time_t> &time, std::vector<float> &speed) : AnalysisBase<float>(time, speed)
    {
        std::cout << "SpeedAnalysis ctor!\n";
    };
    std::string ss{"ss is alive\n"};
};

class ElevationAnalysis : public AnalysisBase<int>
{
public:
    ElevationAnalysis(std::vector<std::time_t> &time, std::vector<int> &ele) : AnalysisBase<int>(time, ele)
    {
        std::cout << "ElevationAnalysis ctor!\n";
    };
};

class Base
{
public:
    Base() { std::cout << "Base c'tor!\n"; }
    std::string basePar{"Base parameter!\n"};
};

class Derived : public Base
{
public:
    Derived() { std::cout << "Derived c'tor!\n"; }
    std::string derivedPar{"Derived parameter!\n"};
};
#endif