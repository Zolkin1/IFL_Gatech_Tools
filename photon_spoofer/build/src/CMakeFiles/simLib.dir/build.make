# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/cmake-3.18.2-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.18.2-Linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build

# Include any dependencies generated for this target.
include src/CMakeFiles/simLib.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/simLib.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/simLib.dir/flags.make

src/CMakeFiles/simLib.dir/simUAV.cpp.o: src/CMakeFiles/simLib.dir/flags.make
src/CMakeFiles/simLib.dir/simUAV.cpp.o: ../src/simUAV.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/simLib.dir/simUAV.cpp.o"
	cd /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simLib.dir/simUAV.cpp.o -c /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/src/simUAV.cpp

src/CMakeFiles/simLib.dir/simUAV.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simLib.dir/simUAV.cpp.i"
	cd /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/src/simUAV.cpp > CMakeFiles/simLib.dir/simUAV.cpp.i

src/CMakeFiles/simLib.dir/simUAV.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simLib.dir/simUAV.cpp.s"
	cd /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/src/simUAV.cpp -o CMakeFiles/simLib.dir/simUAV.cpp.s

# Object files for target simLib
simLib_OBJECTS = \
"CMakeFiles/simLib.dir/simUAV.cpp.o"

# External object files for target simLib
simLib_EXTERNAL_OBJECTS =

src/libsimLib.a: src/CMakeFiles/simLib.dir/simUAV.cpp.o
src/libsimLib.a: src/CMakeFiles/simLib.dir/build.make
src/libsimLib.a: src/CMakeFiles/simLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libsimLib.a"
	cd /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/src && $(CMAKE_COMMAND) -P CMakeFiles/simLib.dir/cmake_clean_target.cmake
	cd /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/simLib.dir/build: src/libsimLib.a

.PHONY : src/CMakeFiles/simLib.dir/build

src/CMakeFiles/simLib.dir/clean:
	cd /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/src && $(CMAKE_COMMAND) -P CMakeFiles/simLib.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/simLib.dir/clean

src/CMakeFiles/simLib.dir/depend:
	cd /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/src /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/src /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/src/CMakeFiles/simLib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/simLib.dir/depend

