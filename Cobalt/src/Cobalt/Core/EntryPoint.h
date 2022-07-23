#pragma once

// Cobalt engine initiation function, to be created in main application
// No need to call main function in main application.
extern Cobalt::Application* Cobalt::CreateApplication();

// TODO: Pass command args into application for debugging purposes
// Main function
int main(int argc, char** argv)
{
	auto app = Cobalt::CreateApplication(); // Create cobalt app
	app->Run(); // Start main engine loop
	delete app; // Delete cobalt app when loop exits

	return 0; // Return 0
}