#include "Application.h"

#define CB_BIND_EVENT_FN(fn) std::bind(&Application::fn, this, std::placeholders::_1)

namespace Cobalt {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		CB_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(CB_BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(CB_BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(CB_BIND_EVENT_FN(OnWindowResize));

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

	void Application::Close()
	{
		m_Running = false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		Close();
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		CB_CORE_TRACE("({0}, {1})", e.GetWidth(), e.GetHeight());

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		return true;
	}

}