#pragma once

#include "LayerStack.h"
#include "../Events/Event.h"

namespace Cobalt
{
	class Scene
	{
	public:
		Scene(const std::string debugName = "Scene")
			: m_DebugName(debugName) {};
		virtual ~Scene() {};

		// Layer push functions
		void PushLayer(std::shared_ptr<Layer> l);
		void PushOverlay(std::shared_ptr<Layer> l);
		// Layer pop functions
		void PopLayer(std::shared_ptr<Layer> l);
		void PopOverlay(std::shared_ptr<Layer> l);

		virtual void OnAdd() {};
		virtual void OnRemove() {};

		virtual bool OnEvent(Event& e) { return false; };
		virtual void OnUpdate(float dt) {};
		
		// Automatically handles layer events and updates
		bool OnLayerEvent(Event& e);
		void OnLayerUpdate(float dt);

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName; // Debug name for scene

		LayerStack m_LayerStack; // Layer stack

	};

	// Print scene debug name
	inline std::ostream& operator<<(std::ostream& os, const Scene& s) { return os << s.GetName(); }
	inline std::ostream& operator<<(std::ostream& os, const Scene* s) { return os << s->GetName(); }
}