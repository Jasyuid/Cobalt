# Cobalt Static Library CMake File
# /Cobalt/Cobalt
#==============================================================================
cmake_minimum_required (VERSION 3.8)

#"src/Cobalt.cpp"to the library
add_library (Cobalt 
	"src/Cobalt.cpp" 
	"src/Cobalt.h"
)

target_include_directories(Cobalt PUBLIC "${PROJECT_SOURCE_DIR}/Cobalt/src")

