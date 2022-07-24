#include "cbpch.h"
#include "EditorCamera.h"

#include "Cobalt/Core/Input.h"

namespace Cobalt
{
	EditorCamera::EditorCamera(const glm::vec3& focus, const float distance)
		: m_Focus(focus), m_Distance(distance)
	{
		m_Yaw = 0.5*std::acos(0.0);
		m_Pitch = 0.5*std::acos(0.0);
		// TODO: Make this not hardcoded
		m_ViewportWidth = 1280;
		m_ViewportHeight = 720;

		// Initialize view and projection matrices
		UpdateView();
		UpdateProjection();
	}

	EditorCamera::~EditorCamera()
	{
	}

	void EditorCamera::UpdateView()
	{
		// Recalculate position for camera based on focus camera orientation
		m_Position = CalculatePosition();

		// Create view matrix
		m_View = glm::lookAt(m_Position, m_Focus, glm::vec3(0, 1, 0));
	}

	void EditorCamera::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		// Create perspective matrix
		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlane, m_Farplane);
	}

	void EditorCamera::OnUpdate(float dt)
	{
		// Calcaulte distance mouse moved
		const glm::vec2 mouse_pos = { Input::GetMouseX(), Input::GetMouseY() };
		glm::vec2 delta = (mouse_pos - m_PrevMousePosition) * 0.01f;
		m_PrevMousePosition = mouse_pos;

		// Move camera with mouse
		if (Input::IsMouseButtonPressed(CB_MOUSE_BUTTON_MIDDLE))
			MousePan(delta);
		else if (Input::IsMouseButtonPressed(CB_MOUSE_BUTTON_LEFT))
			MouseRotate(delta);

		// TODO: Add keyboard controls

		// Update view matrix
		UpdateView();
	}

	void EditorCamera::OnEvent(Event& e)
	{
		// Check for mouse wheel events
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(CB_BIND_EVENT_FN(EditorCamera::OnMouseScroll));
	}

	// Mouse scroll callback function
	bool EditorCamera::OnMouseScroll(MouseScrolledEvent& e)
	{
		// Get scroll magnitude
		float delta = e.GetYOffset();
		// Zoom camera and update view
		MouseZoom(delta);
		UpdateView();
		return true; // Return event has been handled
	}

	void EditorCamera::MousePan(const glm::vec2& delta)
	{
		// Change camera focus to pan camera
		auto speed = PanSpeed();
		m_Focus += GetLeftDirection() * delta.x * speed.first;
		m_Focus += GetUpDirection() * delta.y * speed.second;
	}

	void EditorCamera::MouseRotate(const glm::vec2& delta)
	{
		// Change camera angles
		m_Yaw += delta.x * 1.0f;
		m_Pitch -= delta.y * 1.0f;

		// Stop yaw value from exceeding 2pi or -2pi
		if (m_Yaw > std::acos(-1.0))
			m_Yaw -= 2*std::acos(-1.0);
		else if (m_Yaw < -std::acos(-1.0))
			m_Yaw += 2*std::acos(-1.0);

		// Stop camera when it is looking straight up or down
		if (m_Pitch >= std::acos(0.0))
			m_Pitch = std::acos(0.0) - 0.001f;
		else if (m_Pitch <= -std::acos(0.0))
			m_Pitch = -std::acos(0.0) + 0.001f;

	}

	void EditorCamera::MouseZoom(float delta)
	{
		// Change camera distance to focus point
		m_Distance -= delta * ZoomSpeed();
		// Limit camera to minimum distnace to focus
		if (m_Distance < m_MinDistance)
			m_Distance = m_MinDistance;

	}

	// TODO: Add keyboard pan functionality
	void EditorCamera::KeyboardPan(const glm::vec2& delta)
	{
	}

	// TODO: Change arbitrary numbers?
	std::pair<float, float> EditorCamera::PanSpeed() const
	{
		float x_speed = 1.0f * m_Distance / 10.0f;
		float y_speed = 1.0f * m_Distance / 10.0f;
		return { x_speed, y_speed };
	}

	// TODO: Change arbitrary numbers?
	float EditorCamera::ZoomSpeed() const
	{
		float speed = m_Distance * 0.1f; // Zoom by 10% of current distance to focus
		return speed;
	}

	// Calculate camera orientation and roations
	glm::quat EditorCamera::GetOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}
	glm::vec3 EditorCamera::GetForwardDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	glm::vec3 EditorCamera::GetUpDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	glm::vec3 EditorCamera::GetLeftDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 EditorCamera::CalculatePosition() const
	{
		return m_Focus - GetForwardDirection() * m_Distance;
	}
}