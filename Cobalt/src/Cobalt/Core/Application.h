#pragma once

#include "Window.h"
#include "Cobalt/Events/Event.h"
#include "Cobalt/Events/ApplicationEvent.h"
#include "Cobalt/Events/KeyEvent.h"
#include "KeyCodes.h"
#include "Input.h"
#include "LayerStack.h"
#include "Scene.h"
#include "Cobalt/Rendering/EditorCamera.h"

namespace Cobalt {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void OnEvent(Event& e);
		
		void Run();
		
		void Close();

		inline Window& GetWindow() const { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;

		LayerStack m_LayerStack;

		static Application* s_Instance;

		EditorCamera* camera;
	};

	Application* CreateApplication();

}