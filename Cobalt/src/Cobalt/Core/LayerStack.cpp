#include "cbpch.h"
#include "LayerStack.h"

namespace Cobalt
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		// Detatch all layers
		for (std::shared_ptr<Layer> layer : m_Layers)
		{
			layer->OnDetach();
		}
	}

	void LayerStack::PushLayer(std::shared_ptr<Layer> layer)
	{
		// Push layer to the top of the layer stack
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++; // Increment layer insertion locations
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(std::shared_ptr<Layer> overlay)
	{
		// Add overlay layers to the top of the layer stack
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(std::shared_ptr<Layer> layer)
	{
		// Remove a specified layer from the layer stack
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_Layers.begin() + m_LayerInsertIndex)
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
		else
		{
			CB_CORE_WARN("Unable to find layer '{0}' to pop!", layer);
		}
	}

	void LayerStack::PopOverlay(std::shared_ptr<Layer> overlay)
	{
		// Remove a specified overlay layer from the end of the layer stack
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			overlay->OnDetach();
			m_Layers.erase(it);
		}
		else
		{
			CB_CORE_WARN("Unable to find overlay '{0}' to pop!", overlay);
		}
	}
}