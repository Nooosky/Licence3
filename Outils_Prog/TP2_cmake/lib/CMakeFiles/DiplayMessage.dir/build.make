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
CMAKE_SOURCE_DIR = /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake

# Include any dependencies generated for this target.
include lib/CMakeFiles/DiplayMessage.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/DiplayMessage.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/DiplayMessage.dir/flags.make

lib/CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.o: lib/CMakeFiles/DiplayMessage.dir/flags.make
lib/CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.o: lib/DiplayMessage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.o"
	cd /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.o -c /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib/DiplayMessage.cpp

lib/CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.i"
	cd /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib/DiplayMessage.cpp > CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.i

lib/CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.s"
	cd /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib/DiplayMessage.cpp -o CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.s

lib/CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.o.requires:

.PHONY : lib/CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.o.requires

lib/CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.o.provides: lib/CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.o.requires
	$(MAKE) -f lib/CMakeFiles/DiplayMessage.dir/build.make lib/CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.o.provides.build
.PHONY : lib/CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.o.provides

lib/CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.o.provides.build: lib/CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.o


# Object files for target DiplayMessage
DiplayMessage_OBJECTS = \
"CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.o"

# External object files for target DiplayMessage
DiplayMessage_EXTERNAL_OBJECTS =

lib/libDiplayMessage.a: lib/CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.o
lib/libDiplayMessage.a: lib/CMakeFiles/DiplayMessage.dir/build.make
lib/libDiplayMessage.a: lib/CMakeFiles/DiplayMessage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libDiplayMessage.a"
	cd /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib && $(CMAKE_COMMAND) -P CMakeFiles/DiplayMessage.dir/cmake_clean_target.cmake
	cd /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DiplayMessage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/DiplayMessage.dir/build: lib/libDiplayMessage.a

.PHONY : lib/CMakeFiles/DiplayMessage.dir/build

lib/CMakeFiles/DiplayMessage.dir/requires: lib/CMakeFiles/DiplayMessage.dir/DiplayMessage.cpp.o.requires

.PHONY : lib/CMakeFiles/DiplayMessage.dir/requires

lib/CMakeFiles/DiplayMessage.dir/clean:
	cd /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib && $(CMAKE_COMMAND) -P CMakeFiles/DiplayMessage.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/DiplayMessage.dir/clean

lib/CMakeFiles/DiplayMessage.dir/depend:
	cd /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib /home/bastien/Documents/github/Licence3/Outils_Prog/TP2_cmake/lib/CMakeFiles/DiplayMessage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/DiplayMessage.dir/depend

