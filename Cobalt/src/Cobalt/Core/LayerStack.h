#pragma once

#include "Layer.h"

#include <vector>

namespace Cobalt
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		// The stack of layers
		std::vector<Layer*> m_Layers;
		// Iterator to determine where to push new layers
		unsigned int m_LayerInsertIndex = 0;
	};
}