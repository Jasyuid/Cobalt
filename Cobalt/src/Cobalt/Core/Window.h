#pragma once

#include <iostream>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Cobalt/Events/Event.h"

namespace Cobalt
{
	// Data structure for window creation data
	struct WindowProps
	{
		std::string Title; // Window title
		unsigned int Width, Height; // Window dimensions

		// Default values
		WindowProps(const std::string& title = "Cobalt Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class Window
	{
	public:
		// Function type that will handle event callbacks
		using EventCallbackFn = std::function<void(Event&)>;

		Window(const WindowProps& props);
		~Window();

		void OnUpdate();

		inline unsigned int GetWidth() const { return m_Data.Width; }
		inline unsigned int GetHeight() const { return m_Data.Height; }
		inline bool IsVSync() const { return m_Data.VSync; };

		// Set callback function for events (Called in Application class)
		inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

		void SetVSync(bool enabled);

		// Get actual GLFW window
		inline GLFWwindow* GetNativeWindow() const { return m_Window; }
		// Window creater helper function
		static Window* Create(const WindowProps& props = WindowProps());

	private:
		void Init(const WindowProps& props);
		void Shutdown();

	private:
		GLFWwindow* m_Window; // GLFW window

		// Struct to hold window data
		struct WindowData
		{
			std::string Title; // Window title
			unsigned int Width, Height; // Window dimensions
			bool VSync; // Window vsync status

			EventCallbackFn EventCallback; // Window event callback functions
		};

		WindowData m_Data; // Current window data
	};
}