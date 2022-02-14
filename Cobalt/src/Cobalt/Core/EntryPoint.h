#pragma once

extern Cobalt::Application* Cobalt::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Cobalt::CreateApplication();
	app->Run();
	delete app;

	return 0;
}