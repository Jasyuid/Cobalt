#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Cobalt {

	class Application
	{
	public:
		Application();
		~Application();

		void Run();
		
	private:
	};

	Application* CreateApplication();

}