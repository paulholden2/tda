# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/stu/pholden/TDA

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stu/pholden/TDA/build

# Include any dependencies generated for this target.
include src/init/CMakeFiles/TDA.dir/depend.make

# Include the progress variables for this target.
include src/init/CMakeFiles/TDA.dir/progress.make

# Include the compile flags for this target's objects.
include src/init/CMakeFiles/TDA.dir/flags.make

src/init/CMakeFiles/TDA.dir/main.c.o: src/init/CMakeFiles/TDA.dir/flags.make
src/init/CMakeFiles/TDA.dir/main.c.o: ../src/init/main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/stu/pholden/TDA/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/init/CMakeFiles/TDA.dir/main.c.o"
	cd /home/stu/pholden/TDA/build/src/init && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/TDA.dir/main.c.o   -c /home/stu/pholden/TDA/src/init/main.c

src/init/CMakeFiles/TDA.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TDA.dir/main.c.i"
	cd /home/stu/pholden/TDA/build/src/init && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/stu/pholden/TDA/src/init/main.c > CMakeFiles/TDA.dir/main.c.i

src/init/CMakeFiles/TDA.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TDA.dir/main.c.s"
	cd /home/stu/pholden/TDA/build/src/init && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/stu/pholden/TDA/src/init/main.c -o CMakeFiles/TDA.dir/main.c.s

src/init/CMakeFiles/TDA.dir/main.c.o.requires:
.PHONY : src/init/CMakeFiles/TDA.dir/main.c.o.requires

src/init/CMakeFiles/TDA.dir/main.c.o.provides: src/init/CMakeFiles/TDA.dir/main.c.o.requires
	$(MAKE) -f src/init/CMakeFiles/TDA.dir/build.make src/init/CMakeFiles/TDA.dir/main.c.o.provides.build
.PHONY : src/init/CMakeFiles/TDA.dir/main.c.o.provides

src/init/CMakeFiles/TDA.dir/main.c.o.provides.build: src/init/CMakeFiles/TDA.dir/main.c.o

# Object files for target TDA
TDA_OBJECTS = \
"CMakeFiles/TDA.dir/main.c.o"

# External object files for target TDA
TDA_EXTERNAL_OBJECTS =

src/init/TDA: src/init/CMakeFiles/TDA.dir/main.c.o
src/init/TDA: src/init/CMakeFiles/TDA.dir/build.make
src/init/TDA: src/fs/libTDA_fs.a
src/init/TDA: src/math/libTDA_math.a
src/init/TDA: src/mm/libTDA_mm.a
src/init/TDA: lib/physfs/libTDA_lib_physfs.a
src/init/TDA: src/init/CMakeFiles/TDA.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable TDA"
	cd /home/stu/pholden/TDA/build/src/init && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TDA.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/init/CMakeFiles/TDA.dir/build: src/init/TDA
.PHONY : src/init/CMakeFiles/TDA.dir/build

src/init/CMakeFiles/TDA.dir/requires: src/init/CMakeFiles/TDA.dir/main.c.o.requires
.PHONY : src/init/CMakeFiles/TDA.dir/requires

src/init/CMakeFiles/TDA.dir/clean:
	cd /home/stu/pholden/TDA/build/src/init && $(CMAKE_COMMAND) -P CMakeFiles/TDA.dir/cmake_clean.cmake
.PHONY : src/init/CMakeFiles/TDA.dir/clean

src/init/CMakeFiles/TDA.dir/depend:
	cd /home/stu/pholden/TDA/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stu/pholden/TDA /home/stu/pholden/TDA/src/init /home/stu/pholden/TDA/build /home/stu/pholden/TDA/build/src/init /home/stu/pholden/TDA/build/src/init/CMakeFiles/TDA.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/init/CMakeFiles/TDA.dir/depend

