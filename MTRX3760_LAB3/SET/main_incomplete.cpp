
// a start on a test file for developing your occupancy maps


#include "OccupancyMapHash.h"
#include <iostream>

//-----------------------------------------------------------------------------
int main()
{
  {
    // Create an instance of COccupancyMapHash
    COccupancyMapHash myOccupancyMap;

    // Create a test location with coordinates (3, 4) and add it as an occupied location
    std::pair<int,int> TestLocation = std::make_pair(3, 4);
    myOccupancyMap.AddOccupiedLocation( TestLocation );

    // Display the test location and check if it is occupied
    std::cout << "Location: " << TestLocation.first << " " << TestLocation.second << " returns ";
    std::cout << myOccupancyMap.CheckIsOccupied( TestLocation ) << std::endl;

    // Change the x-coordinate of the test location to 0 and check if it is occupied
    TestLocation.first = 0;
    std::cout << "Location: " << TestLocation.first << " " << TestLocation.second << " returns ";
    std::cout << myOccupancyMap.CheckIsOccupied( TestLocation ) << std::endl;
  }

  {
    // More comprehensive test
    COccupancyMapHash myMap;
    myMap.EvalPerformance( "ExampleObservations_Small.txt", "ExampleNotObserved_Small.txt" );
  }

  return 0;
}

