add_library(simLib simUAV.cpp "${CMAKE_SOURCE_DIR}/inc/simUAV.h")

target_include_directories(simLib PUBLIC ../inc)    # make it public so targets that use this lib will also use this include directory

target_compile_features(simLib PUBLIC cxx_std_11)


add_library(ubxLib UBX.cpp)
target_compile_options(ubxLib PUBLIC "-g")
target_include_directories(ubxLib PUBLIC ../inc)
