# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_SOURCE_DIR = /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib

# Include any dependencies generated for this target.
include CMakeFiles/DiplayMessage.a.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DiplayMessage.a.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DiplayMessage.a.dir/flags.make

CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.o: CMakeFiles/DiplayMessage.a.dir/flags.make
CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.o: DiplayMessage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.o -c /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib/DiplayMessage.cpp

CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib/DiplayMessage.cpp > CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.i

CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib/DiplayMessage.cpp -o CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.s

CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.o.requires:

.PHONY : CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.o.requires

CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.o.provides: CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.o.requires
	$(MAKE) -f CMakeFiles/DiplayMessage.a.dir/build.make CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.o.provides.build
.PHONY : CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.o.provides

CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.o.provides.build: CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.o


# Object files for target DiplayMessage.a
DiplayMessage_a_OBJECTS = \
"CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.o"

# External object files for target DiplayMessage.a
DiplayMessage_a_EXTERNAL_OBJECTS =

libDiplayMessage.a.a: CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.o
libDiplayMessage.a.a: CMakeFiles/DiplayMessage.a.dir/build.make
libDiplayMessage.a.a: CMakeFiles/DiplayMessage.a.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libDiplayMessage.a.a"
	$(CMAKE_COMMAND) -P CMakeFiles/DiplayMessage.a.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DiplayMessage.a.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DiplayMessage.a.dir/build: libDiplayMessage.a.a

.PHONY : CMakeFiles/DiplayMessage.a.dir/build

CMakeFiles/DiplayMessage.a.dir/requires: CMakeFiles/DiplayMessage.a.dir/DiplayMessage.cpp.o.requires

.PHONY : CMakeFiles/DiplayMessage.a.dir/requires

CMakeFiles/DiplayMessage.a.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DiplayMessage.a.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DiplayMessage.a.dir/clean

CMakeFiles/DiplayMessage.a.dir/depend:
	cd /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib/CMakeFiles/DiplayMessage.a.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DiplayMessage.a.dir/depend
