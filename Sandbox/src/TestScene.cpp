#include "TestScene.h"

#include "ShowcaseLayer.h"

TestScene::TestScene()
	: Scene("TestScene")
{
	PushLayer(std::shared_ptr<ShowcaseLayer>(new ShowcaseLayer));
}

TestScene::~TestScene()
{
}

void TestScene::OnEvent(Cobalt::Event& e)
{
	auto l = m_LayerStack.begin();
	auto end = m_LayerStack.end();
	while (l != end)
	{
		l->get()->OnEvent(e);
		l++;
	}
}

void TestScene::OnUpdate(float dt)
{
	auto l = m_LayerStack.begin();
	auto end = m_LayerStack.end();
	while (l != end)
	{
		l->get()->OnUpdate(dt);
		l++;
	}
}
