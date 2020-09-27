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
include app/CMakeFiles/spoofer.dir/depend.make

# Include the progress variables for this target.
include app/CMakeFiles/spoofer.dir/progress.make

# Include the compile flags for this target's objects.
include app/CMakeFiles/spoofer.dir/flags.make

app/CMakeFiles/spoofer.dir/main.cpp.o: app/CMakeFiles/spoofer.dir/flags.make
app/CMakeFiles/spoofer.dir/main.cpp.o: ../app/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object app/CMakeFiles/spoofer.dir/main.cpp.o"
	cd /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/app && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/spoofer.dir/main.cpp.o -c /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/app/main.cpp

app/CMakeFiles/spoofer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spoofer.dir/main.cpp.i"
	cd /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/app && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/app/main.cpp > CMakeFiles/spoofer.dir/main.cpp.i

app/CMakeFiles/spoofer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spoofer.dir/main.cpp.s"
	cd /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/app && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/app/main.cpp -o CMakeFiles/spoofer.dir/main.cpp.s

# Object files for target spoofer
spoofer_OBJECTS = \
"CMakeFiles/spoofer.dir/main.cpp.o"

# External object files for target spoofer
spoofer_EXTERNAL_OBJECTS =

app/spoofer: app/CMakeFiles/spoofer.dir/main.cpp.o
app/spoofer: app/CMakeFiles/spoofer.dir/build.make
app/spoofer: src/libubxLib.a
app/spoofer: src/libsimLib.a
app/spoofer: /usr/local/lib/libGeographic.so.19.0.1
app/spoofer: app/CMakeFiles/spoofer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable spoofer"
	cd /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/app && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/spoofer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
app/CMakeFiles/spoofer.dir/build: app/spoofer

.PHONY : app/CMakeFiles/spoofer.dir/build

app/CMakeFiles/spoofer.dir/clean:
	cd /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/app && $(CMAKE_COMMAND) -P CMakeFiles/spoofer.dir/cmake_clean.cmake
.PHONY : app/CMakeFiles/spoofer.dir/clean

app/CMakeFiles/spoofer.dir/depend:
	cd /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/app /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/app /home/zach/IFL/IFL_Gatech_Tools/photon_spoofer/build/app/CMakeFiles/spoofer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : app/CMakeFiles/spoofer.dir/depend
