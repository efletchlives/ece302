# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /snap/cmake/1445/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1445/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/efletchlives/VsCode/ECE302/ECE302_EHF/project3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/efletchlives/VsCode/ECE302/ECE302_EHF/project3/build

# Utility rule file for starter_download.

# Include any custom commands dependencies for this target.
include CMakeFiles/starter_download.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/starter_download.dir/progress.make

CMakeFiles/starter_download:
	cd /home/efletchlives/VsCode/ECE302/ECE302_EHF/project3 && /snap/cmake/1445/bin/cmake -E tar cfv /home/efletchlives/VsCode/ECE302/ECE302_EHF/project3/build/../project3_starter.zip --format=zip test_XMLParser.cpp XMLParser.hpp XMLParser.cpp Stack.hpp Stack.tpp Bag.hpp Bag.tpp Node.hpp Node.tpp catch.hpp CMakeLists.txt xmlFile.txt TestFile.txt

CMakeFiles/starter_download.dir/codegen:
.PHONY : CMakeFiles/starter_download.dir/codegen

starter_download: CMakeFiles/starter_download
starter_download: CMakeFiles/starter_download.dir/build.make
.PHONY : starter_download

# Rule to build all files generated by this target.
CMakeFiles/starter_download.dir/build: starter_download
.PHONY : CMakeFiles/starter_download.dir/build

CMakeFiles/starter_download.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/starter_download.dir/cmake_clean.cmake
.PHONY : CMakeFiles/starter_download.dir/clean

CMakeFiles/starter_download.dir/depend:
	cd /home/efletchlives/VsCode/ECE302/ECE302_EHF/project3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/efletchlives/VsCode/ECE302/ECE302_EHF/project3 /home/efletchlives/VsCode/ECE302/ECE302_EHF/project3 /home/efletchlives/VsCode/ECE302/ECE302_EHF/project3/build /home/efletchlives/VsCode/ECE302/ECE302_EHF/project3/build /home/efletchlives/VsCode/ECE302/ECE302_EHF/project3/build/CMakeFiles/starter_download.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/starter_download.dir/depend

