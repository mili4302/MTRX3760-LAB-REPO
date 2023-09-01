#ifndef ACCESS_OCCUPANCYMAPHASH_H
#define ACCESS_OCCUPANCYMAPHASH_H


#include "OccupancyMapBase.h"
#include <set>


class COccupancyMapHash : public COccupancyMapBase
{
public:

    // Returns the name of the approach
    std::string GetNameOfApproach() override;

    // Adds a new occupied location to the map
    // Parameters is a pair of integers representing the location (x, y) to be added as occupied
    // then the value is store in member variable, mOccupiedLocations
    void AddOccupiedLocation(std::pair<int, int> aAddLocation) override;

    // Input still is a pair of integers representing the location (x, y) to be checked for occupancy
    // return True if the location is occupied, otherwise false
    bool CheckIsOccupied(std::pair<int, int> aCheckLocation) override;

private:
    std::set<std::pair<int, int>> mOccupiedLocations;  // Set to store occupied locations
};


#endif //ACCESS_OCCUPANCYMAPHASH_H