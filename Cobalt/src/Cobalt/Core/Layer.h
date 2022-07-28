#pragma once

#include "Cobalt/Events/Event.h"

namespace Cobalt
{
	class Layer
	{
	public:
		// Set debug layer name
		Layer(const std::string& debugName = "Layer")
			: m_DebugName(debugName) {};
		virtual ~Layer() {};

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		
		virtual bool OnEvent(Event& event) { return false; };
		virtual void OnUpdate(float dt) {};

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName; // Debug name for layer
	};

	// Print layer debug name
	inline std::ostream& operator<<(std::ostream& os, const Layer& l) { return os << l.GetName(); }
	inline std::ostream& operator<<(std::ostream& os, const Layer* l) { return os << l->GetName(); }
}