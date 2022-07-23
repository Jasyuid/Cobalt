#include "cbpch.h"
#include "Application.h"

#include "Cobalt/Rendering/VertexArray.h"
#include "Cobalt/Rendering/Shader.h"
#include "Cobalt/Rendering/OpenGL.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace Cobalt {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		CB_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(CB_BIND_EVENT_FN(Application::OnEvent));

		camera = new EditorCamera(glm::vec3(0.0f, 0.0f, 0.0f), 5.0f);
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
		dispatcher.Dispatch<WindowCloseEvent>(CB_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(CB_BIND_EVENT_FN(Application::OnWindowResize));

		if (!e.IsHandled())
		{
			camera->OnEvent(e);
			
			/*
			if (e.GetEventType() == EventType::KeyPressed)
			{
				if (((KeyPressedEvent*)&e)->GetKeyCode() == CB_KEY_0)
				{
					CB_TRACE("{0}", e);
				}
			}
			*/
		}
	}

	const float cube_vertices[] = {
		-1.0f,-1.0f,-1.0f,		0.0f, 0.0f, 0.0f, //0
		 1.0f,-1.0f,-1.0f,		1.0f, 0.0f, 0.0f, //1
		-1.0f, 1.0f,-1.0f,		0.0f, 1.0f, 0.0f, //2
		 1.0f, 1.0f,-1.0f,		1.0f, 1.0f, 0.0f, //3
		-1.0f,-1.0f, 1.0f,		0.0f, 0.0f, 1.0f, //4
		 1.0f,-1.0f, 1.0f,		1.0f, 0.0f, 1.0f, //5
		-1.0f, 1.0f, 1.0f,		0.0f, 1.0f, 1.0f, //6
		 1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 1.0f  //7
	};
	const unsigned int cube_indices[] = {
			2, 1, 0, //Front-1
			1, 2, 3, //Front-2
			6, 0, 4, //Left-1
			0, 6, 2, //Left-2
			3, 5, 1, //Right-1
			5, 3, 7, //Right-2
			0, 5, 4, //Bottom-1
			5, 0, 1, //Bottom-2
			6, 3, 2, //Top-1
			3, 6, 7, //Top-2
			4, 5, 6, //Back-1
			7, 6, 5  //Back-2
	};

	void Application::Run()
	{
		VertexBuffer cube_VBO = VertexBuffer(cube_vertices, 8 * 6 * sizeof(float));
		IndexBuffer cube_IBO = IndexBuffer(cube_indices, 12 * 3);

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		VertexArray cube_VAO = VertexArray();
		cube_VAO.AddBuffer(cube_VBO, layout);

		glm::mat4 cubeModel = glm::mat4(1.0f);
		cubeModel = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f)) * cubeModel;
		cubeModel = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)) * cubeModel;

		Shader basicShader = Shader("res/shaders/Basic.glsl");
		basicShader.Bind();
		basicShader.SetUniformMat4("model", cubeModel);
		basicShader.SetUniformMat4("camera", camera->GetCameraMatrix());

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		while (m_Running)
		{
			// Window background
			glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			camera->OnUpdate(0.0f);

			basicShader.Bind();
			basicShader.SetUniformMat4("model", cubeModel);
			basicShader.SetUniformMat4("camera", camera->GetCameraMatrix());

			cube_VAO.Bind();
			cube_IBO.Bind();
			GLCall(glDrawElements(GL_TRIANGLES, cube_IBO.GetCount(), GL_UNSIGNED_INT, nullptr));

			m_Window->OnUpdate();
		}
	}

	void Application::Close()
	{
		m_Running = false; // End main engine loop
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		Close(); // Close window
		return true; // Event handled
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

		return true; // Event handled
	}

}