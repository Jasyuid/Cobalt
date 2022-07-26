#include "cbpch.h"
#include "Scene.h"

namespace Cobalt
{
	Scene::Scene(const std::string& debugName)
		: m_DebugName(debugName)
	{
	}

	void Scene::PushLayer(std::shared_ptr<Layer> l)
	{
		m_LayerStack.PushLayer(l);
	}

	void Scene::PushOverlay(std::shared_ptr<Layer> l)
	{
		m_LayerStack.PushOverlay(l);
	}
}