#pragma once

#include <glm/glm.hpp>

namespace Cobalt
{
	class Light
	{
	public:
		Light(glm::vec3 pos, glm::vec3 col)
			: m_Position(pos), m_Color(col) {};
		~Light() {};

		inline glm::vec3 GetPosition() const { return m_Position; }
		inline glm::vec3 GetColor() const { return m_Color; }

		inline void SetPosition(glm::vec3 pos) { m_Position = pos; }
		inline void Move(glm::vec3 d) { m_Position += d; }
		
		inline void SetColor(glm::vec3 col) { m_Color = col; }

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Color;
	};
}