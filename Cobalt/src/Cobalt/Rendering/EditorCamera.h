#pragma once

#include "Camera.h"
#include "Cobalt/Events/Event.h"
#include "Cobalt/Events/MouseEvent.h"

namespace Cobalt
{
	class EditorCamera : public Camera
	{
	public:
		EditorCamera(const glm::vec3& focus, const float distance);
		~EditorCamera();

		void OnUpdate(float dt);
		void OnEvent(Event& e);

		inline glm::mat4 GetViewMatrix() const { return m_View; }
		inline glm::mat4 GetProjectionMatrix() const { return m_Projection; }
		inline glm::mat4 GetCameraMatrix() const { return m_Projection * m_View; }

		inline glm::vec3 GetPosition() const { return m_Position; }
		inline float GetDistance() const { return m_Distance; }

		glm::quat GetOrientation() const;
		glm::vec3 GetForwardDirection() const;
		glm::vec3 GetUpDirection() const;
		glm::vec3 GetLeftDirection() const;

		glm::vec3 CalculatePosition() const;

		inline void SetViewportSize(float width, float height) { m_ViewportWidth = width; m_ViewportHeight = height; UpdateProjection(); }

	private:
		void UpdateView();
		void UpdateProjection();

		bool OnMouseScroll(MouseScrolledEvent& e);

		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);
		void MouseZoom(float delta);

		void KeyboardPan(const glm::vec2& delta);

		std::pair<float, float> PanSpeed() const;
		float ZoomSpeed() const;

	private:
		float m_FOV = 45.0f, m_AspectRatio = 16.0f/9.0f, m_NearPlane = 0.1f, m_Farplane = 1000.0f;

		glm::mat4 m_Projection, m_View;
		
		glm::vec3 m_Focus;
		float m_Distance;
		float m_Yaw, m_Pitch;
		
		glm::vec3 m_Position;

		glm::vec2 m_PrevMousePosition = { 0.0f, 0.0f };
		float m_MinDistance = 0.1f; // TODO: Make a cleaner solution

		float m_ViewportWidth, m_ViewportHeight;
	};
}