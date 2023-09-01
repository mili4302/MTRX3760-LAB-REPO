// OccupancyMap_Base.h
//
// Base class for an occupancy map
// 
// This defines the interface for an occupancy map that can :
// 1) record a set of observations as known occupied locations, and
// 2) test of a given location has been observed as being occupied
//
// The base class knows how to evaluate the performance of a given occupancy map implementation by :
// 1) loading a pair of test files, one defining a list of test points corresponding to observed occupied
// locations, and one defining a set of test points corresponding to unoccupied space,
// 2) populating the occupancy map with observed points by calling its AddOccupiedLocation function, and
// 3) testing the occupancy map by checking that it returns correct values for the loaded test data
//
// The test also reports on how long it takes to run through all the test points, to allow a comparison
// of speed.
// 
// Initial revision: Donald G Dansereau, 2022

#ifndef _OCCUPANCYMAPBASE_H
#define _OCCUPANCYMAPBASE_H

#include <string>
#include <utility>        // std::pair
#include <vector>

//----------------------------------------------------------------------------------------------------------
// Base class for an occupancy map.
// An occupancy map accepts observed points, one at a time, to keep track of what parts of space are occupied.
// It offers a function to check if a given point in space is occupied.
//
// This implementation works on coordinates provided as std::pair<int,int>.
// It is acceptable to assume all observed points will be integer, non-negative, and less than 2048
//
// The base class includes a built-in function for evaluating the correctness and speed of a particular derived 
// class implementation of the occupancy map. See EvalPerformance() for details.

class COccupancyMapBase
{
  public:
   
    // Return the name of the approach as a string, for display purposes
    virtual std::string GetNameOfApproach() = 0;

    // Add a location observed to be occupied to the map
    virtual void AddOccupiedLocation(std::pair<int,int> Location) = 0;
    
    // Check if a location is occupied
    virtual bool CheckIsOccupied( std::pair<int,int> Location ) = 0;
        
    //---Evaluation-----------------------------------------------------------------------------------------
    // Evaluate the performance of an occupancy map.
    // Loads a local file called FName containing observations of occupied map locations.
    // These are loaded into the map via the derived class AddOccupiedLocation function,
    // then validated via the derived class CheckIsOccupied function.
    // If any unexpected results are found, these are output to std::cout.
    // The whole process is timed, and the timing results printed to std::cout.
    void EvalPerformance( std::string ObservationsFName, std::string NotObservedFName );
    

  private:
    //--Data------------------------------------------------------------------------------------------------
    std::vector<std::pair<int,int>> mObservedPoints;    // A set of test points that correspond to observations
    std::vector<std::pair<int,int>> mNotObservedPoints; // A set of test points that don't correspond to observations
   
    //--Helper Functions------------------------------------------------------------------------------------
    void PopulateForEval( std::string ObservationsFName, std::string NotObservedFName );   // load a file of test points for testing
    double FindTotRuntime();                     // validate and time a derived-class map, returns runtime in ms
};



#endif // _OCCUPANCYMAPBASE_H

