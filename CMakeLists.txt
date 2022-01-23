cmake_minimum_required(VERSION 3.20)
project(assignment2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_STANDARD 20)

add_executable(GeneticAlgorithm main.cpp City.cpp City.hpp Tour.cpp Tour.hpp Population.cpp Population.hpp)
