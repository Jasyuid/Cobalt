#pragma once

#include "Window.h"
#include "Cobalt/Events/Event.h"
#include "Cobalt/Events/ApplicationEvent.h"
#include "Cobalt/Events/KeyEvent.h"	
#include "Cobalt/Events/MouseEvent.h"
#include "Input.h"

namespace Cobalt {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void Run();
		
		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnKeyPress(KeyPressedEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		static Application* s_Instance;
	};

	Application* CreateApplication();

}