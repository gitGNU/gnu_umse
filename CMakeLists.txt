cmake_minimum_required(VERSION 2.6)

# Project
project(umse)

set(EXECUTABLE_OUTPUT_PATH bin)
set(CMAKE_CFLAGS_DEBUG "-g -Wall")
set(CMAKE_CFLAGS_RELEASE "-O3 -D_REENTRANT -fomit-frame-pointer")

# Set release default cmake_build_type
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
	set(CMAKE_VERBOSE_MAKEFILE 1)
endif(CMAKE_BUILD_TYPE MATCHES "Debug")

include_directories(inc)

add_executable(
	umse
	src/browse.c
	src/config.c
	src/file.c
	src/input.c
	src/listview.c
	src/output.c
	src/screen.c
	src/static.c
	src/str.c
	src/sys.c
	src/umse.c
)

target_link_libraries(
	umse
	ao
	pthread
	ncurses
	panel
)
