# Cobalt Static Library CMake File
# /Cobalt/Cobalt
#==============================================================================
cmake_minimum_required (VERSION 3.8)

#"src/Cobalt.cpp"to the library
add_library (Cobalt 
	"src/Cobalt.h"
	"src/Cobalt/Core/EntryPoint.h"
	"src/Cobalt/Core/Application.h"
	"src/Cobalt/Core/Application.cpp")

target_include_directories(Cobalt PUBLIC "${PROJECT_SOURCE_DIR}/Cobalt/src")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory ("vendor/glfw")
target_link_libraries(Cobalt glfw)

add_subdirectory ("vendor/glad")
target_link_libraries(Cobalt glad)

