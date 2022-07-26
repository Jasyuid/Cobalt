#pragma once

#include "LayerStack.h"
#include "../Events/Event.h"

namespace Cobalt
{
	class Scene
	{
	public:
		Scene(const std::string& debugName = "Scene");
		virtual ~Scene() {};
		
		void PushLayer(std::shared_ptr<Layer> l);
		void PushOverlay(std::shared_ptr<Layer> l);

		virtual void OnEvent(Event& e) {};
		virtual void OnUpdate(float dt) {};

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName; // Debug name for scene

		LayerStack m_LayerStack; // Layer stack

	};

	// Print scene debug name
	inline std::ostream& operator<<(std::ostream& os, const Scene& s) { return os << s.GetName(); }
}