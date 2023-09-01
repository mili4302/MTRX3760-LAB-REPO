cmake_minimum_required(VERSION 3.24)
project(VECTOR)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(VECTOR
        main_incomplete.cpp
        OccupancyMapBase.cpp
        OccupancyMapBase.h
        OccupancyMapHash.cpp
        OccupancyMapHash.h)
