#include "FileManager.h"

void FileManager::addFile(std::string fileName)
{
    File newFile(fileName);
    if (newFile.isOK())
        _files.push_back(std::move(std::make_unique<File>(newFile)));
}

void FileManager::loadFile(int filePosition)
{
    if (filePosition < _files.size() -1 )
    {
        std::cout << "The file wasn't found.\n";
        return;
    }
    std::unique_ptr<Data> newData = std::make_unique<Data>();
    newData->readFromFile(_files[filePosition]->filePath());
    newData->calculateSpeedAndDistanceTracks();
    _data.push_back(std::move(newData));
}

void FileManager::printAnalysis(int filePostion, int trkPos)
{

    std::cout << "\n ** Track analysis **\n";

    if (filePostion < _files.size() - 1)
    {
        std::cout << "Oops the file wasn't valid. Try entering it again.\n";
        return;
    }
    std::cout << "\nFile name: " << _files[filePostion]->fileName() << "\n";
    if (trkPos < _data.size() - 1)
    {
        std::cout << "Oops that track wasn't valid. Try reloading it.\n";
        return;
    }

    std::shared_ptr<Trk> trk = _data[filePostion]->getTrackByIndex(trkPos);
    SpeedAnalysis aSpeedAnalysis(trk->time, trk->speed);
    ElevationAnalysis anEleAnalysis(trk->time, trk->ele);

    std::cout << "Track name: " << trk->name << "\n";
    std::cout << "Distance traveled: " << trk->distanceTraveled << " km\n";
    std::cout << "Track duration: " << aSpeedAnalysis.trackTimeFormatted() << " hh:mm:ss\n";

    std::cout << "\n** SpeedAnalysis **\n";
    std::cout << "Max speed: " << aSpeedAnalysis.max() << " km/hr\n";
    std::cout << "Stopped time: " << aSpeedAnalysis.stoppedTimeMin() << " min\n";
    std::cout << "Mean speed while moving: " << aSpeedAnalysis.meanMovingSpeedKmPerH() << " km/hr\n";

    std::cout << "\n** ElevationAnalysis **\n";
    std::cout << "Max elevation: " << anEleAnalysis.max() << " m\n";
    std::cout << "Min elevation: " << anEleAnalysis.min() << " m\n";
    std::cout << "Climb: " << anEleAnalysis.assentInMeters() << " m\n";
    std::cout << "Decent: " << anEleAnalysis.decentInMeters() << " m\n";

    std::cout << "\n\n";
}