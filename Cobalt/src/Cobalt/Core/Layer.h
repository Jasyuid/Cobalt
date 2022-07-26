#pragma once

#include "Cobalt/Events/Event.h"

namespace Cobalt
{
	class Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer() {};

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		
		virtual void OnEvent(Event& event) {};
		virtual void OnUpdate(float dt) {};

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName; // Debug name for layer
	};

	// Print layer debug name
	inline std::ostream& operator<<(std::ostream& os, const Layer& l) { return os << l.GetName(); }
}