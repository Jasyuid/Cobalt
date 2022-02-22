#include "EditorCamera.h"

#include "Cobalt/Core/Input.h"

namespace Cobalt
{
	EditorCamera::EditorCamera(const glm::vec3& focus, const float distance)
		: m_Focus(focus), m_Distance(distance)
	{
		m_Yaw = 0.5*std::acos(0.0);
		m_Pitch = 0.5*std::acos(0.0);
		m_ViewportWidth = 1280;
		m_ViewportHeight = 720;

		UpdateView();
		UpdateProjection();
	}

	EditorCamera::~EditorCamera()
	{

	}

	void EditorCamera::UpdateView()
	{
		m_Position = CalculatePosition();

		m_View = glm::lookAt(m_Position, m_Focus, glm::vec3(0, 1, 0));
	}

	void EditorCamera::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlane, m_Farplane);
	}

	void EditorCamera::OnUpdate(float dt)
	{
		const glm::vec2 mouse_pos = { Input::GetMouseX(), Input::GetMouseY() };
		glm::vec2 delta = (mouse_pos - m_PrevMousePosition) * 0.01f;
		m_PrevMousePosition = mouse_pos;

		if (Input::IsMouseButtonPressed(CB_MOUSE_BUTTON_MIDDLE))
			MousePan(delta);
		else if (Input::IsMouseButtonPressed(CB_MOUSE_BUTTON_LEFT))
			MouseRotate(delta);

		UpdateView();
	}

	void EditorCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(CB_BIND_EVENT_FN(EditorCamera::OnMouseScroll));
	}

	bool EditorCamera::OnMouseScroll(MouseScrolledEvent& e)
	{
		float delta = e.GetYOffset() * 0.1;
		MouseZoom(delta);
		UpdateView();
		return true; // TODO: Check what this should return
	}

	void EditorCamera::MousePan(const glm::vec2& delta)
	{
		auto speed = PanSpeed();
		m_Focus += GetLeftDirection() * delta.x * speed.first;
		m_Focus += GetUpDirection() * delta.y * speed.second;
	}

	void EditorCamera::MouseRotate(const glm::vec2& delta)
	{
		m_Yaw += delta.x * 1.0f;
		m_Pitch -= delta.y * 1.0f;

		if (m_Yaw > std::acos(-1.0))
			m_Yaw -= 2*std::acos(-1.0);
		else if (m_Yaw < -std::acos(-1.0))
			m_Yaw += 2*std::acos(-1.0);

		if (m_Pitch >= std::acos(0.0))
			m_Pitch = std::acos(0.0) - 0.001f;
		else if (m_Pitch <= -std::acos(0.0))
			m_Pitch = -std::acos(0.0) + 0.001f;

	}

	void EditorCamera::MouseZoom(float delta)
	{
		m_Distance -= delta * ZoomSpeed();
		if (m_Distance < m_MinDistance)
		{
			m_Distance = m_MinDistance;
		}

	}

	void EditorCamera::KeyboardPan(const glm::vec2& delta)
	{

	}

	std::pair<float, float> EditorCamera::PanSpeed() const
	{
		float x_speed = 1.0f;
		float y_speed = 1.0f;
		return { x_speed, y_speed };
	}

	float EditorCamera::ZoomSpeed() const
	{
		float distance = m_Distance * 0.35f;
		float speed = distance * distance;
		speed = std::min(speed, 100.0f);
		return speed;
	}

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