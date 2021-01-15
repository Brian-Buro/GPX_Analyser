cmake_minimum_required(VERSION 3.7)

# Project settings
project(GPX_Analyser)

# Compiler flags
add_definitions(-std=c++17)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

# Find all files in src
file(GLOB srcFiles src/*.cpp) 

# Add executable
add_executable(GPX_Analyser ${srcFiles})
