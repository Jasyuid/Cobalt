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

		// Get iterators for bottom and top of layer stack
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers; // The stack of layers
		unsigned int m_LayerInsertIndex = 0; // Iterator to determine where to push new layers
	};
}