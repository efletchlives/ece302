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
CMAKE_COMMAND = /snap/cmake/1461/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1461/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/efletchlives/VsCode/ECE302/ECE302_EHF/homework8/Lec20

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/efletchlives/VsCode/ECE302/ECE302_EHF/homework8/Lec20/build

# Include any dependencies generated for this target.
include CMakeFiles/test-dict.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test-dict.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test-dict.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test-dict.dir/flags.make

CMakeFiles/test-dict.dir/codegen:
.PHONY : CMakeFiles/test-dict.dir/codegen

CMakeFiles/test-dict.dir/test_dict.cpp.o: CMakeFiles/test-dict.dir/flags.make
CMakeFiles/test-dict.dir/test_dict.cpp.o: /home/efletchlives/VsCode/ECE302/ECE302_EHF/homework8/Lec20/test_dict.cpp
CMakeFiles/test-dict.dir/test_dict.cpp.o: CMakeFiles/test-dict.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/efletchlives/VsCode/ECE302/ECE302_EHF/homework8/Lec20/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test-dict.dir/test_dict.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test-dict.dir/test_dict.cpp.o -MF CMakeFiles/test-dict.dir/test_dict.cpp.o.d -o CMakeFiles/test-dict.dir/test_dict.cpp.o -c /home/efletchlives/VsCode/ECE302/ECE302_EHF/homework8/Lec20/test_dict.cpp

CMakeFiles/test-dict.dir/test_dict.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test-dict.dir/test_dict.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/efletchlives/VsCode/ECE302/ECE302_EHF/homework8/Lec20/test_dict.cpp > CMakeFiles/test-dict.dir/test_dict.cpp.i

CMakeFiles/test-dict.dir/test_dict.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test-dict.dir/test_dict.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/efletchlives/VsCode/ECE302/ECE302_EHF/homework8/Lec20/test_dict.cpp -o CMakeFiles/test-dict.dir/test_dict.cpp.s

# Object files for target test-dict
test__dict_OBJECTS = \
"CMakeFiles/test-dict.dir/test_dict.cpp.o"

# External object files for target test-dict
test__dict_EXTERNAL_OBJECTS =

test-dict: CMakeFiles/test-dict.dir/test_dict.cpp.o
test-dict: CMakeFiles/test-dict.dir/build.make
test-dict: CMakeFiles/test-dict.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/efletchlives/VsCode/ECE302/ECE302_EHF/homework8/Lec20/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-dict"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-dict.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test-dict.dir/build: test-dict
.PHONY : CMakeFiles/test-dict.dir/build

CMakeFiles/test-dict.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test-dict.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test-dict.dir/clean

CMakeFiles/test-dict.dir/depend:
	cd /home/efletchlives/VsCode/ECE302/ECE302_EHF/homework8/Lec20/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/efletchlives/VsCode/ECE302/ECE302_EHF/homework8/Lec20 /home/efletchlives/VsCode/ECE302/ECE302_EHF/homework8/Lec20 /home/efletchlives/VsCode/ECE302/ECE302_EHF/homework8/Lec20/build /home/efletchlives/VsCode/ECE302/ECE302_EHF/homework8/Lec20/build /home/efletchlives/VsCode/ECE302/ECE302_EHF/homework8/Lec20/build/CMakeFiles/test-dict.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/test-dict.dir/depend

