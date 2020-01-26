#include "pch.h"

#include "Core\Application.h"
#include "Core\Layers\GameLayer.h"
//#include <SDL.h>


class RayTracerApp : public Application
{
public:
	RayTracerApp()
	{

		//	PushOverlay(new PrettyEngine::ImGuiLayer());
		PushLayer(new GameLayer());

	}
	~RayTracerApp()
	{

	}

private:


};

Application* CreateApplication()
{

	return new RayTracerApp();
}



int main(int argc, char *argv[])
{
	

	auto app = CreateApplication();
	app->Run();
	delete app;

//	std::cin.get();
////================================================================================================


	
	return EXIT_SUCCESS;
}



