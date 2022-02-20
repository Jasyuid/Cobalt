#include "Application.h"

#define CB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Cobalt {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		CB_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		dispatcher.Dispatch<KeyPressedEvent>(std::bind(&Application::OnKeyPress, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseMovedEvent>(std::bind(&Application::OnMouseMoved, this, std::placeholders::_1));
		

	}

	void Application::Run()
	{
		while (m_Running)
		{
			// Window background
			glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Window->OnUpdate();

			if (Input::IsMouseButtonPressed(CB_MOUSE_BUTTON_MIDDLE))
			{
				CB_CORE_TRACE("Middle mouse button is down!");
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnKeyPress(KeyPressedEvent& e)
	{
		CB_TRACE("KeyPressed: {0}", e.GetKeyCode());
		return true;
	}

	bool Application::OnMouseMoved(MouseMovedEvent& e)
	{
		CB_TRACE("MouseMoved: ({0}, {1})", e.GetX(), e.GetY());
		return true;
	}


}