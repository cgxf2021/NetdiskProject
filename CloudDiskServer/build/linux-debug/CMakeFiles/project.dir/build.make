# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /home/smxrfx/Qt/Tools/CMake/bin/cmake

# The command to remove a file.
RM = /home/smxrfx/Qt/Tools/CMake/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug

# Include any dependencies generated for this target.
include CMakeFiles/project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project.dir/flags.make

project_autogen/EWIEGA46WW/qrc_resource.cpp: /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/resource.qrc
project_autogen/EWIEGA46WW/qrc_resource.cpp: CMakeFiles/project_autogen.dir/AutoRcc_resource_EWIEGA46WW_Info.json
project_autogen/EWIEGA46WW/qrc_resource.cpp: /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/config.cfg
project_autogen/EWIEGA46WW/qrc_resource.cpp: /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/cloud.db
project_autogen/EWIEGA46WW/qrc_resource.cpp: /home/smxrfx/Qt/6.6.0/gcc_64/./libexec/rcc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic RCC for resource.qrc"
	/home/smxrfx/Qt/Tools/CMake/bin/cmake -E cmake_autorcc /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/CMakeFiles/project_autogen.dir/AutoRcc_resource_EWIEGA46WW_Info.json Debug

CMakeFiles/project.dir/project_autogen/mocs_compilation.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/project_autogen/mocs_compilation.cpp.o: project_autogen/mocs_compilation.cpp
CMakeFiles/project.dir/project_autogen/mocs_compilation.cpp.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/project.dir/project_autogen/mocs_compilation.cpp.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project.dir/project_autogen/mocs_compilation.cpp.o -MF CMakeFiles/project.dir/project_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/project.dir/project_autogen/mocs_compilation.cpp.o -c /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/project_autogen/mocs_compilation.cpp

CMakeFiles/project.dir/project_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/project_autogen/mocs_compilation.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/project_autogen/mocs_compilation.cpp > CMakeFiles/project.dir/project_autogen/mocs_compilation.cpp.i

CMakeFiles/project.dir/project_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/project_autogen/mocs_compilation.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/project_autogen/mocs_compilation.cpp -o CMakeFiles/project.dir/project_autogen/mocs_compilation.cpp.s

CMakeFiles/project.dir/main.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/main.cpp.o: /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/main.cpp
CMakeFiles/project.dir/main.cpp.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/project.dir/main.cpp.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project.dir/main.cpp.o -MF CMakeFiles/project.dir/main.cpp.o.d -o CMakeFiles/project.dir/main.cpp.o -c /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/main.cpp

CMakeFiles/project.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/main.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/main.cpp > CMakeFiles/project.dir/main.cpp.i

CMakeFiles/project.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/main.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/main.cpp -o CMakeFiles/project.dir/main.cpp.s

CMakeFiles/project.dir/widget.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/widget.cpp.o: /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/widget.cpp
CMakeFiles/project.dir/widget.cpp.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/project.dir/widget.cpp.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project.dir/widget.cpp.o -MF CMakeFiles/project.dir/widget.cpp.o.d -o CMakeFiles/project.dir/widget.cpp.o -c /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/widget.cpp

CMakeFiles/project.dir/widget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/widget.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/widget.cpp > CMakeFiles/project.dir/widget.cpp.i

CMakeFiles/project.dir/widget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/widget.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/widget.cpp -o CMakeFiles/project.dir/widget.cpp.s

CMakeFiles/project.dir/source/cloud_server.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/source/cloud_server.cpp.o: /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/source/cloud_server.cpp
CMakeFiles/project.dir/source/cloud_server.cpp.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/project.dir/source/cloud_server.cpp.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project.dir/source/cloud_server.cpp.o -MF CMakeFiles/project.dir/source/cloud_server.cpp.o.d -o CMakeFiles/project.dir/source/cloud_server.cpp.o -c /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/source/cloud_server.cpp

CMakeFiles/project.dir/source/cloud_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/source/cloud_server.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/source/cloud_server.cpp > CMakeFiles/project.dir/source/cloud_server.cpp.i

CMakeFiles/project.dir/source/cloud_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/source/cloud_server.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/source/cloud_server.cpp -o CMakeFiles/project.dir/source/cloud_server.cpp.s

CMakeFiles/project.dir/source/cloud_socket.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/source/cloud_socket.cpp.o: /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/source/cloud_socket.cpp
CMakeFiles/project.dir/source/cloud_socket.cpp.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/project.dir/source/cloud_socket.cpp.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project.dir/source/cloud_socket.cpp.o -MF CMakeFiles/project.dir/source/cloud_socket.cpp.o.d -o CMakeFiles/project.dir/source/cloud_socket.cpp.o -c /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/source/cloud_socket.cpp

CMakeFiles/project.dir/source/cloud_socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/source/cloud_socket.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/source/cloud_socket.cpp > CMakeFiles/project.dir/source/cloud_socket.cpp.i

CMakeFiles/project.dir/source/cloud_socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/source/cloud_socket.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/source/cloud_socket.cpp -o CMakeFiles/project.dir/source/cloud_socket.cpp.s

CMakeFiles/project.dir/source/protocol.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/source/protocol.cpp.o: /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/source/protocol.cpp
CMakeFiles/project.dir/source/protocol.cpp.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/project.dir/source/protocol.cpp.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project.dir/source/protocol.cpp.o -MF CMakeFiles/project.dir/source/protocol.cpp.o.d -o CMakeFiles/project.dir/source/protocol.cpp.o -c /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/source/protocol.cpp

CMakeFiles/project.dir/source/protocol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/source/protocol.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/source/protocol.cpp > CMakeFiles/project.dir/source/protocol.cpp.i

CMakeFiles/project.dir/source/protocol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/source/protocol.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/source/protocol.cpp -o CMakeFiles/project.dir/source/protocol.cpp.s

CMakeFiles/project.dir/source/database_operator.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/source/database_operator.cpp.o: /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/source/database_operator.cpp
CMakeFiles/project.dir/source/database_operator.cpp.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/project.dir/source/database_operator.cpp.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project.dir/source/database_operator.cpp.o -MF CMakeFiles/project.dir/source/database_operator.cpp.o.d -o CMakeFiles/project.dir/source/database_operator.cpp.o -c /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/source/database_operator.cpp

CMakeFiles/project.dir/source/database_operator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/source/database_operator.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/source/database_operator.cpp > CMakeFiles/project.dir/source/database_operator.cpp.i

CMakeFiles/project.dir/source/database_operator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/source/database_operator.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/source/database_operator.cpp -o CMakeFiles/project.dir/source/database_operator.cpp.s

CMakeFiles/project.dir/project_autogen/EWIEGA46WW/qrc_resource.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/project_autogen/EWIEGA46WW/qrc_resource.cpp.o: project_autogen/EWIEGA46WW/qrc_resource.cpp
CMakeFiles/project.dir/project_autogen/EWIEGA46WW/qrc_resource.cpp.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/project.dir/project_autogen/EWIEGA46WW/qrc_resource.cpp.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project.dir/project_autogen/EWIEGA46WW/qrc_resource.cpp.o -MF CMakeFiles/project.dir/project_autogen/EWIEGA46WW/qrc_resource.cpp.o.d -o CMakeFiles/project.dir/project_autogen/EWIEGA46WW/qrc_resource.cpp.o -c /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/project_autogen/EWIEGA46WW/qrc_resource.cpp

CMakeFiles/project.dir/project_autogen/EWIEGA46WW/qrc_resource.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/project_autogen/EWIEGA46WW/qrc_resource.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/project_autogen/EWIEGA46WW/qrc_resource.cpp > CMakeFiles/project.dir/project_autogen/EWIEGA46WW/qrc_resource.cpp.i

CMakeFiles/project.dir/project_autogen/EWIEGA46WW/qrc_resource.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/project_autogen/EWIEGA46WW/qrc_resource.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/project_autogen/EWIEGA46WW/qrc_resource.cpp -o CMakeFiles/project.dir/project_autogen/EWIEGA46WW/qrc_resource.cpp.s

# Object files for target project
project_OBJECTS = \
"CMakeFiles/project.dir/project_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/project.dir/main.cpp.o" \
"CMakeFiles/project.dir/widget.cpp.o" \
"CMakeFiles/project.dir/source/cloud_server.cpp.o" \
"CMakeFiles/project.dir/source/cloud_socket.cpp.o" \
"CMakeFiles/project.dir/source/protocol.cpp.o" \
"CMakeFiles/project.dir/source/database_operator.cpp.o" \
"CMakeFiles/project.dir/project_autogen/EWIEGA46WW/qrc_resource.cpp.o"

# External object files for target project
project_EXTERNAL_OBJECTS =

project: CMakeFiles/project.dir/project_autogen/mocs_compilation.cpp.o
project: CMakeFiles/project.dir/main.cpp.o
project: CMakeFiles/project.dir/widget.cpp.o
project: CMakeFiles/project.dir/source/cloud_server.cpp.o
project: CMakeFiles/project.dir/source/cloud_socket.cpp.o
project: CMakeFiles/project.dir/source/protocol.cpp.o
project: CMakeFiles/project.dir/source/database_operator.cpp.o
project: CMakeFiles/project.dir/project_autogen/EWIEGA46WW/qrc_resource.cpp.o
project: CMakeFiles/project.dir/build.make
project: /home/smxrfx/Qt/6.6.0/gcc_64/lib/libQt6Widgets.so.6.6.0
project: /home/smxrfx/Qt/6.6.0/gcc_64/lib/libQt6Network.so.6.6.0
project: /home/smxrfx/Qt/6.6.0/gcc_64/lib/libQt6Sql.so.6.6.0
project: /home/smxrfx/Qt/6.6.0/gcc_64/lib/libQt6Gui.so.6.6.0
project: /usr/lib/x86_64-linux-gnu/libGLX.so
project: /usr/lib/x86_64-linux-gnu/libOpenGL.so
project: /home/smxrfx/Qt/6.6.0/gcc_64/lib/libQt6Core.so.6.6.0
project: CMakeFiles/project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project.dir/build: project
.PHONY : CMakeFiles/project.dir/build

CMakeFiles/project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/project.dir/clean

CMakeFiles/project.dir/depend: project_autogen/EWIEGA46WW/qrc_resource.cpp
	cd /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug /home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/build/linux-debug/CMakeFiles/project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/project.dir/depend
