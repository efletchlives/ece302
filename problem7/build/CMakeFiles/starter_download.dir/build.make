# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = /snap/cmake/1457/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1457/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/efletchlives/VsCode/ECE302/ECE302_EHF/problem7

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/efletchlives/VsCode/ECE302/ECE302_EHF/problem7/build

# Utility rule file for starter_download.

# Include any custom commands dependencies for this target.
include CMakeFiles/starter_download.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/starter_download.dir/progress.make

CMakeFiles/starter_download:
	cd /home/efletchlives/VsCode/ECE302/ECE302_EHF/problem7 && /snap/cmake/1457/bin/cmake -E tar cfv /home/efletchlives/VsCode/ECE302/ECE302_EHF/problem7/build/../problem7_starter.zip --format=zip test_bst.cpp binary_search_tree.hpp binary_search_tree.tpp CMakeLists.txt catch.hpp

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
	cd /home/efletchlives/VsCode/ECE302/ECE302_EHF/problem7/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/efletchlives/VsCode/ECE302/ECE302_EHF/problem7 /home/efletchlives/VsCode/ECE302/ECE302_EHF/problem7 /home/efletchlives/VsCode/ECE302/ECE302_EHF/problem7/build /home/efletchlives/VsCode/ECE302/ECE302_EHF/problem7/build /home/efletchlives/VsCode/ECE302/ECE302_EHF/problem7/build/CMakeFiles/starter_download.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/starter_download.dir/depend

