# Sandbox Executable CMake File
# /Cobalt/Sandbox
#==============================================================================
cmake_minimum_required (VERSION 3.8)

# Add source code to executable
add_executable(Sandbox 
	"src/Sandbox.cpp" 
)

target_link_libraries(Sandbox PUBLIC Cobalt) 
