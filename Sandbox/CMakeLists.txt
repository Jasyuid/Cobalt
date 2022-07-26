# Sandbox Executable CMake File
# /Cobalt/Sandbox
#==============================================================================
cmake_minimum_required (VERSION 3.8)

# Add source code to executable
add_executable(Sandbox 
	"src/Sandbox.cpp" 
	"src/TestScene.h" "src/TestScene.cpp" "src/ShowcaseLayer.h" "src/ShowcaseLayer.cpp")

target_link_libraries(Sandbox PUBLIC Cobalt) 
