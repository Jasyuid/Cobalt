#include "Cobalt.h"

#include <iostream>

class Sandbox : public Cobalt::Application
{
public:
	Sandbox()
	{
		std::cout << "App Created\n";
	}
	~Sandbox()
	{
		std::cout << "App Deleted\n";
	}
};

Cobalt::Application* Cobalt::CreateApplication()
{
	return new Sandbox();
}
