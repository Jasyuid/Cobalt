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

void TestScene::OnAdd()
{

}

void TestScene::OnRemove()
{

}

bool TestScene::OnEvent(Cobalt::Event& e)
{
	return e.IsHandled();
}

void TestScene::OnUpdate(float dt)
{
	
}
