#include "cbpch.h"
#include "Scene.h"

namespace Cobalt
{
	// TODO: Move this to layer stack

	// Push a layer to the layer stack
	void Scene::PushLayer(std::shared_ptr<Layer> l)
	{
		m_LayerStack.PushLayer(l);
		CB_CORE_INFO("Pushed layer '{0}'", l);
	}

	// Push an overlay to the layer stack
	void Scene::PushOverlay(std::shared_ptr<Layer> l)
	{
		m_LayerStack.PushOverlay(l);
		CB_CORE_INFO("Pushed overlay '{0}'", l);
	}

	// Pop a layer from the layer stack
	void Scene::PopLayer(std::shared_ptr<Layer> l)
	{
		m_LayerStack.PopLayer(l);
		CB_CORE_INFO("Popped layer '{0}'", l);
	}

	// Pop an overlay from the layer stack
	void Scene::PopOverlay(std::shared_ptr<Layer> l)
	{
		m_LayerStack.PopOverlay(l);
		CB_CORE_INFO("Popped overlay '{0}'", l);
	}

	// Sends event to all layers on stack
	bool Scene::OnLayerEvent(Event& e)
	{
		auto l = m_LayerStack.begin();
		auto end = m_LayerStack.end();
		while (l != end)
		{
			// If event is fully handled by layer, exit function
			if (l->get()->OnEvent(e))
				break;
			l++;
		}
		// Return is event is fully handled
		return e.IsHandled();
	}

	// Updates all layers on the stack
	void Scene::OnLayerUpdate(float dt)
	{
		auto l = m_LayerStack.begin();
		auto end = m_LayerStack.end();
		while (l != end)
		{
			l->get()->OnUpdate(dt);
			l++;
		}
	}
}