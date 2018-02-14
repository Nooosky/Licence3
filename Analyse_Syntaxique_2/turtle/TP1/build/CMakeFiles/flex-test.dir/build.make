# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_SOURCE_DIR = /home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1/build

# Include any dependencies generated for this target.
include CMakeFiles/flex-test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/flex-test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/flex-test.dir/flags.make

lexer.c: ../lexer.l
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "[FLEX][lexer] Building scanner with flex 2.6.1"
	cd /home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1 && /usr/bin/flex --header-file=/home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1/build/lexer.h -o/home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1/build/lexer.c lexer.l

CMakeFiles/flex-test.dir/lexer.c.o: CMakeFiles/flex-test.dir/flags.make
CMakeFiles/flex-test.dir/lexer.c.o: lexer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/flex-test.dir/lexer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/flex-test.dir/lexer.c.o   -c /home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1/build/lexer.c

CMakeFiles/flex-test.dir/lexer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/flex-test.dir/lexer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1/build/lexer.c > CMakeFiles/flex-test.dir/lexer.c.i

CMakeFiles/flex-test.dir/lexer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/flex-test.dir/lexer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1/build/lexer.c -o CMakeFiles/flex-test.dir/lexer.c.s

CMakeFiles/flex-test.dir/lexer.c.o.requires:

.PHONY : CMakeFiles/flex-test.dir/lexer.c.o.requires

CMakeFiles/flex-test.dir/lexer.c.o.provides: CMakeFiles/flex-test.dir/lexer.c.o.requires
	$(MAKE) -f CMakeFiles/flex-test.dir/build.make CMakeFiles/flex-test.dir/lexer.c.o.provides.build
.PHONY : CMakeFiles/flex-test.dir/lexer.c.o.provides

CMakeFiles/flex-test.dir/lexer.c.o.provides.build: CMakeFiles/flex-test.dir/lexer.c.o


CMakeFiles/flex-test.dir/main.c.o: CMakeFiles/flex-test.dir/flags.make
CMakeFiles/flex-test.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/flex-test.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/flex-test.dir/main.c.o   -c /home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1/main.c

CMakeFiles/flex-test.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/flex-test.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1/main.c > CMakeFiles/flex-test.dir/main.c.i

CMakeFiles/flex-test.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/flex-test.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1/main.c -o CMakeFiles/flex-test.dir/main.c.s

CMakeFiles/flex-test.dir/main.c.o.requires:

.PHONY : CMakeFiles/flex-test.dir/main.c.o.requires

CMakeFiles/flex-test.dir/main.c.o.provides: CMakeFiles/flex-test.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/flex-test.dir/build.make CMakeFiles/flex-test.dir/main.c.o.provides.build
.PHONY : CMakeFiles/flex-test.dir/main.c.o.provides

CMakeFiles/flex-test.dir/main.c.o.provides.build: CMakeFiles/flex-test.dir/main.c.o


# Object files for target flex-test
flex__test_OBJECTS = \
"CMakeFiles/flex-test.dir/lexer.c.o" \
"CMakeFiles/flex-test.dir/main.c.o"

# External object files for target flex-test
flex__test_EXTERNAL_OBJECTS =

flex-test: CMakeFiles/flex-test.dir/lexer.c.o
flex-test: CMakeFiles/flex-test.dir/main.c.o
flex-test: CMakeFiles/flex-test.dir/build.make
flex-test: CMakeFiles/flex-test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable flex-test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/flex-test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/flex-test.dir/build: flex-test

.PHONY : CMakeFiles/flex-test.dir/build

CMakeFiles/flex-test.dir/requires: CMakeFiles/flex-test.dir/lexer.c.o.requires
CMakeFiles/flex-test.dir/requires: CMakeFiles/flex-test.dir/main.c.o.requires

.PHONY : CMakeFiles/flex-test.dir/requires

CMakeFiles/flex-test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/flex-test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/flex-test.dir/clean

CMakeFiles/flex-test.dir/depend: lexer.c
	cd /home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1 /home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1 /home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1/build /home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1/build /home/near/L3/Licence3/Analyse_Syntaxique/turtle/TP1/build/CMakeFiles/flex-test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/flex-test.dir/depend

