# Cobalt Static Library CMake File
# /Cobalt/Cobalt
#==============================================================================
cmake_minimum_required (VERSION 3.8)

add_library (Cobalt 
	"src/Cobalt.h"
	"src/Cobalt/Core/EntryPoint.h"
	"src/Cobalt/Core/Application.h"
	"src/Cobalt/Core/Application.cpp" 
	"src/Cobalt/Core/Logger.h" 
	"src/Cobalt/Core/Logger.cpp"  
	"src/cbpch.h"  
	"src/Cobalt/Core/Core.h"  
	"src/Cobalt/Core/Window.h" 
	"src/Cobalt/Core/Window.cpp" 
	"src/Cobalt/Events/Event.h" 
	"src/Cobalt/Events/ApplicationEvent.h" 
	"src/Cobalt/Events/KeyEvent.h" 
	"src/Cobalt/Events/MouseEvent.h" 
	"src/Cobalt/Core/Input.h" 
	"src/Cobalt/Core/Input.cpp" 
	"src/Cobalt/Core/KeyCodes.h" 
	"src/Cobalt/Core/MouseButtonCodes.h" 
	"src/Cobalt/Core/LayerStack.h" 
	"src/Cobalt/Core/LayerStack.cpp" 
	"src/Cobalt/Core/Layer.h"
	"src/Cobalt/Core/Layer.cpp" 
	"src/Cobalt/Rendering/OpenGL.h" 
	"src/Cobalt/Rendering/Buffer.h" 
	"src/Cobalt/Rendering/Buffer.cpp" 
	"src/Cobalt/Rendering/VertexArray.h" 
	"src/Cobalt/Rendering/VertexArray.cpp" 
	"src/Cobalt/Rendering/VertexBufferLayout.h" 
	"src/Cobalt/Rendering/Shader.h" 
	"src/Cobalt/Rendering/Shader.cpp" 
	"src/Cobalt/Rendering/Camera.h" 
	"src/Cobalt/Rendering/EditorCamera.h" 
	"src/Cobalt/Rendering/EditorCamera.cpp" "src/Cobalt/Rendering/Texture.h" "src/Cobalt/Rendering/Texture.cpp")

target_include_directories(Cobalt PUBLIC "${PROJECT_SOURCE_DIR}/Cobalt/src")

target_precompile_headers(Cobalt PRIVATE "src/cbpch.h")

if(WIN32)
	target_compile_definitions(Cobalt PRIVATE CB_PLATFORM_WINDOWS)
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory ("vendor/glfw")
target_link_libraries(Cobalt glfw)

add_subdirectory ("vendor/glad")
target_link_libraries(Cobalt glad)

add_subdirectory("vendor/glm")
target_link_libraries(Cobalt glm)

add_subdirectory("vendor/stb_image")
target_link_libraries(Cobalt stb_image)

