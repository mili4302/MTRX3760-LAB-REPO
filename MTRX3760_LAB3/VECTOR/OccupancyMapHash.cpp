#include "OccupancyMapHash.h"


//-- Constructor --------------------------------------------------------------------
COccupancyMapHash::COccupancyMapHash()
{
  const int MapSize = 250;

  // Create an empty row
  std::vector<bool> emptyRow(MapSize, false);

  // Initialize the occupancy map using the empty row
  mOccupiedMap.resize(MapSize, emptyRow);
}


//-- return the approach name -------------------------------------------------------
std::string COccupancyMapHash::GetNameOfApproach()
{
  // Here, use "Vector" to indicate that we use "Vector" to store location information.
  return "Vector";
}


//-- Store occupied location to member variable -------------------------------------
void COccupancyMapHash::AddOccupiedLocation(std::pair<int, int> aLocationToAdd)
{
  // Mark the specified location as occupied
  mOccupiedMap[aLocationToAdd.first][aLocationToAdd.second] = true;
}


//-- Check whether the location is occupied -------------------------------------------
bool COccupancyMapHash::CheckIsOccupied(std::pair<int, int> aLocationToChck)
{
  // Check if the specified location is occupied in the map
  return mOccupiedMap[aLocationToChck.first][aLocationToChck.second];
}