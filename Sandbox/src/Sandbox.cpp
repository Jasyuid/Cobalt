#include "Cobalt.h"
#include "Cobalt/Core/EntryPoint.h"

#include "TestScene.h"

class Sandbox : public Cobalt::Application
{
public:
	Sandbox()
	{
		SwapScene(std::shared_ptr<Cobalt::Scene>(new TestScene()));
	}
	~Sandbox()
	{
	}
};

Cobalt::Application* Cobalt::CreateApplication()
{
	return new Sandbox();
}
