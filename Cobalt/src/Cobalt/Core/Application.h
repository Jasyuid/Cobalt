#pragma once

namespace Cobalt {

	class Application
	{
	public:
		Application();
		~Application();

		void Run();
		
	private:
	};

	Application* CreateApplication();

}