#pragma once

#include "LayerStack.h"
#include "../Events/Event.h"

namespace Cobalt
{
	class Scene
	{
	public:
		Scene(const std::string& debugName = "Scene");
		virtual ~Scene();
		
		virtual void OnUpdate() {};
		virtual void OnEvent(Event& event) {};

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName; // Debug name for scene

		LayerStack m_LayerStack; // Layer stack

	};

	// Print scene debug name
	inline std::ostream& operator<<(std::ostream& os, const Scene& s) { return os << s.GetName(); }
}