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

		// Mouse scroll callback
		bool OnMouseScroll(MouseScrolledEvent& e);

		// Mouse camera movement
		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);
		void MouseZoom(float delta);

		// Keyboard camera movement
		void KeyboardPan(const glm::vec2& delta);

		// Calculate current camera speed
		std::pair<float, float> PanSpeed() const;
		float ZoomSpeed() const;

	private:
		float m_FOV = 45.0f, m_AspectRatio = 16.0f/9.0f, m_NearPlane = 0.1f, m_Farplane = 1000.0f; // Default camera values

		glm::mat4 m_Projection, m_View; // Camera matrices
		
		glm::vec3 m_Focus; // Focus point
		float m_Distance; // Distance from focus point
		float m_Yaw, m_Pitch; // Pitch and yaw of camera
		
		glm::vec3 m_Position; // Poition of camera

		glm::vec2 m_PrevMousePosition = { 0.0f, 0.0f }; // Used to calculate mouse speed for camera speed
		float m_MinDistance = 0.1f; // Minimum distance of camera to focus point

		float m_ViewportWidth, m_ViewportHeight; // Current window size
	};
}