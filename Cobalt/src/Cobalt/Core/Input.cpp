#include "cbpch.h"
#include "Input.h"

#include "Application.h"

#include <GLFW/glfw3.h>

namespace Cobalt
{
	bool Input::IsKeyPressed(unsigned int keycode)
	{
		// Get GLFW window and check if a key is pressed
		GLFWwindow* window = Application::Get().GetWindow().GetNativeWindow();
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(unsigned int button)
	{
		// Get GLFW window and check if a mousebutton is pressed
		GLFWwindow* window = Application::Get().GetWindow().GetNativeWindow();
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		// Get GLFW window and get mouse position
		GLFWwindow* window = Application::Get().GetWindow().GetNativeWindow();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	// Just get mouse x or y coordinate
	float Input::GetMouseX()
	{
		float pos = GetMousePosition().first;
		return pos;
	}
	float Input::GetMouseY()
	{
		float pos = GetMousePosition().second;
		return pos;
	}
}