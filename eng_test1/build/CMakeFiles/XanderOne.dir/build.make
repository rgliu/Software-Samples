# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/richardliu/Desktop/eng_test1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/richardliu/Desktop/eng_test1/build

# Include any dependencies generated for this target.
include CMakeFiles/XanderOne.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/XanderOne.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/XanderOne.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/XanderOne.dir/flags.make

CMakeFiles/XanderOne.dir/main.cpp.o: CMakeFiles/XanderOne.dir/flags.make
CMakeFiles/XanderOne.dir/main.cpp.o: /Users/richardliu/Desktop/eng_test1/main.cpp
CMakeFiles/XanderOne.dir/main.cpp.o: CMakeFiles/XanderOne.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/richardliu/Desktop/eng_test1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/XanderOne.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/XanderOne.dir/main.cpp.o -MF CMakeFiles/XanderOne.dir/main.cpp.o.d -o CMakeFiles/XanderOne.dir/main.cpp.o -c /Users/richardliu/Desktop/eng_test1/main.cpp

CMakeFiles/XanderOne.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/XanderOne.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/richardliu/Desktop/eng_test1/main.cpp > CMakeFiles/XanderOne.dir/main.cpp.i

CMakeFiles/XanderOne.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/XanderOne.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/richardliu/Desktop/eng_test1/main.cpp -o CMakeFiles/XanderOne.dir/main.cpp.s

# Object files for target XanderOne
XanderOne_OBJECTS = \
"CMakeFiles/XanderOne.dir/main.cpp.o"

# External object files for target XanderOne
XanderOne_EXTERNAL_OBJECTS =

XanderOne: CMakeFiles/XanderOne.dir/main.cpp.o
XanderOne: CMakeFiles/XanderOne.dir/build.make
XanderOne: proclib/libProcLib.a
XanderOne: CMakeFiles/XanderOne.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/richardliu/Desktop/eng_test1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable XanderOne"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/XanderOne.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/XanderOne.dir/build: XanderOne
.PHONY : CMakeFiles/XanderOne.dir/build

CMakeFiles/XanderOne.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/XanderOne.dir/cmake_clean.cmake
.PHONY : CMakeFiles/XanderOne.dir/clean

CMakeFiles/XanderOne.dir/depend:
	cd /Users/richardliu/Desktop/eng_test1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/richardliu/Desktop/eng_test1 /Users/richardliu/Desktop/eng_test1 /Users/richardliu/Desktop/eng_test1/build /Users/richardliu/Desktop/eng_test1/build /Users/richardliu/Desktop/eng_test1/build/CMakeFiles/XanderOne.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/XanderOne.dir/depend

