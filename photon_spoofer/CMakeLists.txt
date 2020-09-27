cmake_minimum_required(VERSION 3.18)

project(photon_spoofer
        VERSION 1.0
        DESCRIPTION "A simulator for particle photon vicon parsing"
        LANGUAGES CXX)


add_subdirectory(src)
add_subdirectory(app)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
