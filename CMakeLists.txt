cmake_minimum_required(VERSION 3.15)
project(project2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(project2
        main.cpp
        Maze.cpp
        Maze.hpp
        sampleInputForMaze.txt)
