#include "Cobalt.h"

class Sandbox : public Cobalt::Application
{
public:
	Sandbox()
	{
	}
	~Sandbox()
	{
	}
};

Cobalt::Application* Cobalt::CreateApplication()
{
	CB_TRACE("Starting application...");
	return new Sandbox();
}
