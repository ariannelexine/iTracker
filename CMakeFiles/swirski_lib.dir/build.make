# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/arianne/APT_Test/pupil_tracker_standalone

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arianne/APT_Test

# Include any dependencies generated for this target.
include CMakeFiles/swirski_lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/swirski_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/swirski_lib.dir/flags.make

CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.o: CMakeFiles/swirski_lib.dir/flags.make
CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.o: pupil_tracker_standalone/swirski_pupil/PupilTracker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arianne/APT_Test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.o -c /home/arianne/APT_Test/pupil_tracker_standalone/swirski_pupil/PupilTracker.cpp

CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arianne/APT_Test/pupil_tracker_standalone/swirski_pupil/PupilTracker.cpp > CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.i

CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arianne/APT_Test/pupil_tracker_standalone/swirski_pupil/PupilTracker.cpp -o CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.s

CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.o.requires:

.PHONY : CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.o.requires

CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.o.provides: CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.o.requires
	$(MAKE) -f CMakeFiles/swirski_lib.dir/build.make CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.o.provides.build
.PHONY : CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.o.provides

CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.o.provides.build: CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.o


CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.o: CMakeFiles/swirski_lib.dir/flags.make
CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.o: pupil_tracker_standalone/swirski_pupil/cvx.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arianne/APT_Test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.o -c /home/arianne/APT_Test/pupil_tracker_standalone/swirski_pupil/cvx.cpp

CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arianne/APT_Test/pupil_tracker_standalone/swirski_pupil/cvx.cpp > CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.i

CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arianne/APT_Test/pupil_tracker_standalone/swirski_pupil/cvx.cpp -o CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.s

CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.o.requires:

.PHONY : CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.o.requires

CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.o.provides: CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.o.requires
	$(MAKE) -f CMakeFiles/swirski_lib.dir/build.make CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.o.provides.build
.PHONY : CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.o.provides

CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.o.provides.build: CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.o


CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.o: CMakeFiles/swirski_lib.dir/flags.make
CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.o: pupil_tracker_standalone/swirski_pupil/utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arianne/APT_Test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.o -c /home/arianne/APT_Test/pupil_tracker_standalone/swirski_pupil/utils.cpp

CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arianne/APT_Test/pupil_tracker_standalone/swirski_pupil/utils.cpp > CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.i

CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arianne/APT_Test/pupil_tracker_standalone/swirski_pupil/utils.cpp -o CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.s

CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.o.requires:

.PHONY : CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.o.requires

CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.o.provides: CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.o.requires
	$(MAKE) -f CMakeFiles/swirski_lib.dir/build.make CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.o.provides.build
.PHONY : CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.o.provides

CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.o.provides.build: CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.o


# Object files for target swirski_lib
swirski_lib_OBJECTS = \
"CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.o" \
"CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.o" \
"CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.o"

# External object files for target swirski_lib
swirski_lib_EXTERNAL_OBJECTS =

libswirski_lib.a: CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.o
libswirski_lib.a: CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.o
libswirski_lib.a: CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.o
libswirski_lib.a: CMakeFiles/swirski_lib.dir/build.make
libswirski_lib.a: CMakeFiles/swirski_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arianne/APT_Test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libswirski_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/swirski_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/swirski_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/swirski_lib.dir/build: libswirski_lib.a

.PHONY : CMakeFiles/swirski_lib.dir/build

CMakeFiles/swirski_lib.dir/requires: CMakeFiles/swirski_lib.dir/swirski_pupil/PupilTracker.cpp.o.requires
CMakeFiles/swirski_lib.dir/requires: CMakeFiles/swirski_lib.dir/swirski_pupil/cvx.cpp.o.requires
CMakeFiles/swirski_lib.dir/requires: CMakeFiles/swirski_lib.dir/swirski_pupil/utils.cpp.o.requires

.PHONY : CMakeFiles/swirski_lib.dir/requires

CMakeFiles/swirski_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/swirski_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/swirski_lib.dir/clean

CMakeFiles/swirski_lib.dir/depend:
	cd /home/arianne/APT_Test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arianne/APT_Test/pupil_tracker_standalone /home/arianne/APT_Test/pupil_tracker_standalone /home/arianne/APT_Test /home/arianne/APT_Test /home/arianne/APT_Test/CMakeFiles/swirski_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/swirski_lib.dir/depend

