#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>

struct trk
{
    std::vector<float> time;
    std::vector<float> ele;
    std::vector<std::pair<float, float>> trkpt;
    std::vector<float> speed;
    std::string name;
};

class Data
{
public:
    void parseFile(std::string &fileName);

private:
    std::vector<trk> _tracks;
};

#endif