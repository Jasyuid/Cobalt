#pragma once

#include "Cobalt/Events/Event.h"

namespace Cobalt
{
	class Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetatch() {};
		virtual void OnUpdate() {};
		virtual void OnEvent(Event& event) {};

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		// Debug name for layer
		std::string m_DebugName;
	};
}