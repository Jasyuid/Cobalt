#include "Application.h"

namespace Cobalt {

	Application::Application()
	{
		
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		if (!glfwInit())
			std::cout << "GLFW Failed!\n";
		else
			std::cout << "Success!\n";

		glfwTerminate();
	}

}