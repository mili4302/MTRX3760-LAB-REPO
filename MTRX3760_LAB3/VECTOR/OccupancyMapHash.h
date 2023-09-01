#ifndef ACCESS_OCCUPANCYMAPHASH_H
#define ACCESS_OCCUPANCYMAPHASH_H


#include "OccupancyMapBase.h"
#include <vector>
#include <utility>

class COccupancyMapHash : public COccupancyMapBase
{
public:
    // Constructor to initialize the size of the map
    COccupancyMapHash();

    // Returns the name of the approach
    std::string GetNameOfApproach() override;

    // Adds a new occupied location to the map
    // Parameters is a pair of integers representing the location (x, y) to be added as occupied
    // then the value is store in member variable, mOccupiedLocations
    void AddOccupiedLocation(std::pair<int, int> aLocationToAdd) override;

    // Input still is a pair of integers representing the location (x, y) to be checked for occupancy
    // return True if the location is occupied, otherwise false
    bool CheckIsOccupied(std::pair<int, int> aLocationToChck) override;

private:
    std::vector< std::vector<bool>> mOccupiedMap;  // 2D vector to store the occupancy map
};


#endif //ACCESS_OCCUPANCYMAPHASH_H