#include "cbpch.h"
#include "Window.h"

#include "Cobalt/Events/ApplicationEvent.h"
#include "Cobalt/Events/KeyEvent.h"
#include "Cobalt/Events/MouseEvent.h"

namespace Cobalt
{
	// Global variable so GLFW is only initialized once (If multiple windows were ever created)
	static bool s_GLFWInitialized = false;

	// Callback function for GLFW errors
	void GLFWErrorCallback(int error, const char* description)
	{
		CB_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	// Window creator helper function
	Window* Window::Create(const WindowProps& props)
	{
		return new Window(props);
	}

	Window::Window(const WindowProps& props)
	{
		Init(props);
	}

	Window::~Window()
	{
		Shutdown();
	}

	void Window::Init(const WindowProps& props)
	{
		// Store window data from input struct
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		CB_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		// Initialize GLFW
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			CB_CORE_ASSERT(success, "Could not initialize GLFW!"); // Check if initialzed
			glfwSetErrorCallback(GLFWErrorCallback); // Set error callback
			s_GLFWInitialized = true;
		}

		// Set desired OpenGL requirements
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create window and set up glad
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CB_CORE_ASSERT(status, "Failed to initialize Glad!");
		// Associate window data struct with the glfw window (Make the data globally accessible)
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true); // TODO: Make this not hardcoded

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			// Get window info
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			// Create an event and send it to the event callback function
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			// Get window info
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			// Create an event and send it to the event callback function
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		// Callback based on physical key press
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			// Get window info
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			// Key pressed event
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			// Key released event
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			// Key held down beyond initial detection
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			}
		});

		// Callback based on unicode data being sent, 
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				// Get window info
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				// Create an event and send it to the event callback function
				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			// Get window info
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			// Get window info
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			// Get window info
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void Window::Shutdown()
	{
		CB_CORE_INFO("Destroying Window");
		glfwDestroyWindow(m_Window); // Destroy GLFW window
		CB_CORE_INFO("Terminating GLFW");
		glfwTerminate(); // Close GLFW
	}

	void Window::OnUpdate()
	{
		glfwPollEvents(); // Detect any events that occured so callbacks can be used
		glfwSwapBuffers(m_Window); // Swap current buffer being displayed on window (Change the frame)
	}

	void Window::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}
}