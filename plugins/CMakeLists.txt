cmake_minimum_required(VERSION 2.6)




#----------------/ Global settings \-----------------

set(LIBRARY_OUTPUT_PATH lib)
set(CMAKE_CFLAGS_DEBUG "-g -Wall")
set(CMAKE_CFLAGS_RELEASE "-O3 -fomit-frame-pointer")
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif(NOT CMAKE_BUILD_TYPE)
if(CMAKE_BUILD_TYPE MATCHES "Debug")
	set(CMAKE_VERBOSE_MAKEFILE 1)
endif(CMAKE_BUILD_TYPE MATCHES "Debug")
include_directories(inc /usr/include/libmodplug)




#====================================================
#                   SC68-Plugin 
#====================================================

project(sc68-plugin)
add_library(
	sc68-plugin
	SHARED
	sc68-plugin/sc68-plugin.c
)
target_link_libraries(
	sc68-plugin
	sc68
	unice68
	file68
)
install(
	TARGETS
	sc68-plugin
	DESTINATION
	"~/.umse/plugins"
)




#====================================================
#                   MOD-Plugin 
#====================================================

project(mod-plugin)
add_library(
	mod-plugin
	SHARED
	mod-plugin/mod-plugin.c
)
target_link_libraries(
	mod-plugin
	modplug
)
install(
	TARGETS
	mod-plugin
	DESTINATION
	"~/.umse/plugins"
)
