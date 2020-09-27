add_executable(spoofer main.cpp)

find_package(GeographicLib REQUIRED)

#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

target_compile_features(spoofer PRIVATE cxx_std_17)

target_link_libraries(spoofer ubxLib)
target_link_libraries(spoofer simLib)
target_link_libraries(spoofer ${GeographicLib_LIBRARIES})
