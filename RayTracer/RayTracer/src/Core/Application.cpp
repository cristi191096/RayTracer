#include "pch.h"
#include "Application.h"


Application* Application::s_Instance = nullptr;

Application::Application()
{
	Log::Init();
	ASSERT(!s_Instance, "Application already exists!");
	s_Instance = this;
	srand(time(NULL));
	m_Window = std::make_unique<Window>(Window());
	m_Running = true;
	PrintOptions();
}

Application::~Application()
{
}

void Application::PrintOptions() 
{
	WARN("================== ALMOST REAL-TIME RAYTRACER ===================");
	WARN("|	U/D/L/R ARROWS	-> MOVE					      |");
	WARN("|	  R		-> REFLECTIONS ON/OFF			      |");
	WARN("|	  H		-> HARD SHADOWS ON			      |");
	WARN("|	  S		-> INCREASE NUMBER OF SAMPLES (SOFT SHADOWS)  |");
	WARN("|	  J		-> JITTER ON/OFF			      |");
	WARN("|	  ]		-> INCREASE LIGHT INTESITY		      |");
	WARN("|	  [		-> DECREASE LIGHT INTESITY		      |");
	WARN("|	SPACE		-> QUERY PERFORMANCE ON/OFF		      |");
	WARN("|	  0		-> PRINT MENU		   		      |");
	WARN("=================================================================");
}

void Application::OnEvent()
{
	
	SDL_Event ev;

	while (SDL_PollEvent(&ev) != 0)
	{
		//Handle window events
		m_Window->OnEvent(ev);

		//User requests quit
		if (ev.type == SDL_QUIT)
		{
			m_Running = false;

		}
		if (ev.type == SDL_KEYDOWN)
		{
			if (ev.key.keysym.sym == SDLK_0) 
			{
				PrintOptions();
			}
		}

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(ev);
		}
	}
}


void Application::PushLayer(Layer * layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}

void Application::PushOverlay(Layer * layer)
{
	m_LayerStack.PushOverlay(layer);
	layer->OnAttach();
}


void Application::Run()
{
	
	while (m_Running)
	{

		if (!m_Window->IsMinimised()) 
		{
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
		}
		
		OnEvent();

		m_Window->OnUpdate();
		SDL_Delay(33);
	}

	m_Window->Shutdown();
}

void Application::Init()
{
}


