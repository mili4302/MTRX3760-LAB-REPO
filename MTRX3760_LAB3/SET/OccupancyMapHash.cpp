#include "OccupancyMapHash.h"

//-- return the approach name -------------------------------------------------------
std::string COccupancyMapHash::GetNameOfApproach()
{
  // Here, use "set" to indicate that we use "set" to store location information.
  return "Set";
}


//-- Store occupied location to member variable -------------------------------------
void COccupancyMapHash::AddOccupiedLocation(std::pair<int, int> aAddLocation)
{
  // Insert the specified coordinates into the set of occupied locations
  mOccupiedLocations.insert(aAddLocation);
}


//-- Check whether the location is occupied -------------------------------------------
bool COccupancyMapHash::CheckIsOccupied(std::pair<int, int> aCheckLocation)
{
  // Use the find function of the set to check if the given
  // coordinates exist in the set of occupied locations
  // If found, it means the location is occupied and return true; otherwise, return false
  return mOccupiedLocations.find(aCheckLocation) != mOccupiedLocations.end();
}