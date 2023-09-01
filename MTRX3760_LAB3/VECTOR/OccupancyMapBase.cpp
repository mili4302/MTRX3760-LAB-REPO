// OccupancyMap_Base.cpp
//
// Base class for an occupancy map
// 
// Initial revision: Donald G Dansereau, 2022

#include "OccupancyMapBase.h"

#include <iostream>
#include <string>
#include <utility>        // std::pair
#include <vector>
#include <chrono>         // for measuring duration of function call
#include <fstream>        // ifstream

//--Load up a file and populate the map for testing-------------------------------------------------------
void COccupancyMapBase::PopulateForEval( std::string ObservationsFName, std::string NotObservedFName )
{
  // Load the test points corresponding to observed occupied points in space
  // Note these go both into the base class record of points for testing, and into the map being evaluated
  {
    std::cout << "Loading the file of observations... " << ObservationsFName << std::endl;
    std::ifstream InFile( ObservationsFName );
    std::pair<int,int> ReadVal;  
      
    while( InFile.good() )
    {
      InFile >> ReadVal.first;
      InFile >> ReadVal.second;
      
      if( InFile.eof() )
      {
        break;
      }
      
      mObservedPoints.push_back( ReadVal );  // add to the tester's store of observed points
      AddOccupiedLocation( ReadVal );        // add to the derived class store of observed points
      // std::cout << "Read " << ReadVal.first << " " << ReadVal.second << std::endl;
    }
    std::cout << "PopulateForEval loaded " << mObservedPoints.size() << " observed test points" << std::endl;
  }
  
  // Load the test points corresponding to free space
  // Note these go only into the base class record of points for testing, not the map being evaluated
  {
    std::cout << "Loading the file of test points that don't correspond to observations... " << NotObservedFName << std::endl;
    std::ifstream InFile( NotObservedFName );
    std::pair<int,int> ReadVal;  
      
    while( InFile.good() )
    {
      InFile >> ReadVal.first;
      InFile >> ReadVal.second;
      
      if( InFile.eof() )
      {
        break;
      }
      
      mNotObservedPoints.push_back( ReadVal );  // add to the tester's store of unobserved points
      // std::cout << "Read " << ReadVal.first << " " << ReadVal.second << std::endl;
    }
    std::cout << "PopulateForEval loaded " << mNotObservedPoints.size() << " unobserved test points" << std::endl;
  }
  
}

//--Evaluate the performance of the derived class-----------------------------------------------------------
void COccupancyMapBase::EvalPerformance( std::string ObservationsFName, std::string NotObservedFName )
{
  std::cout << "Evaluating " << GetNameOfApproach() << " using test points from " 
            << ObservationsFName << " and " << NotObservedFName 
            << std::endl;
      
  // Populate the map
  PopulateForEval( ObservationsFName, NotObservedFName );
  
  // Evaluate
  double MeanRuntime = FindTotRuntime();

  // Report
  std::cout << "Total time to test all points: " << MeanRuntime << " ms" << std::endl;      
};


//--Helper function to validate and time----------------------------------------------------------
double COccupancyMapBase::FindTotRuntime()
{
  std::cout << "Measuring runtime..." << std::endl;
  double Result = -1;
  
  // Start a timer
  auto t1 = std::chrono::high_resolution_clock::now();

  // Test recall of existing occupied locations
  for( auto TestPoint: mObservedPoints )
  {
    // std::cout << "Checking " << TestPoint.first << " " << TestPoint.second << std::endl;
    bool TestResult = CheckIsOccupied( TestPoint );   // call the derived-class occupancy check
    if( TestResult != true )                          // these should all return "true"
    {
      std::cout << "ERROR!" << std::endl;
      std::cout << "  Observed point at " << TestPoint.first << " " << TestPoint.second << " claims to be unoccupied" << std::endl;
    }
  }

  // Test that unobserved points are also treated correctly
  for( auto TestPoint: mNotObservedPoints )
  {
    // std::cout << "Checking " << TestPoint.first << " " << TestPoint.second << std::endl;
    bool TestResult = CheckIsOccupied( TestPoint );   // call the derived-class occupancy check
    if( TestResult != false )                         // these should all return "false"
    {
      std::cout << "ERROR!" << std::endl;
      std::cout << "  Unobserved point at " << TestPoint.first << " " << TestPoint.second << " claims to be occupied" << std::endl;
    }
  }
  
  // Stop the timer and compute time elapsed
  auto t2 = std::chrono::high_resolution_clock::now();  // keep track of time
  std::chrono::duration<double, std::milli> Duration = t2 - t1;

  // Return timing result
  Result = Duration.count();
  return Result;
}

