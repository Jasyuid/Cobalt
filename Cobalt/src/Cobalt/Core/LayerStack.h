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

		void PushLayer(std::shared_ptr<Layer> layer);
		void PushOverlay(std::shared_ptr<Layer> overlay);
		void PopLayer(std::shared_ptr<Layer> layer);
		void PopOverlay(std::shared_ptr<Layer> overlay);

		// Get iterators for bottom and top of layer stack
		std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
		std::vector<std::shared_ptr<Layer>>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<std::shared_ptr<Layer>> m_Layers; // The stack of layers
		unsigned int m_LayerInsertIndex = 0; // Iterator to determine where to push new layers
	};
}