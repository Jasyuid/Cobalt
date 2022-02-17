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
			std::cout << "GLFW init failed!\n";

		glm::vec3 test_vec = glm::vec3(1.5f, 1.0f, 1.0f);
		std::cout << test_vec.x << std::endl;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GLFWwindow* window = glfwCreateWindow(640, 480, "Test Window", NULL, NULL);
		if (!window)
			std::cout << "Window creation failed!\n";
		
		glfwMakeContextCurrent(window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		// Jank pause
		std::string s;
		std::cin >> s;

		glfwTerminate();
	}

}