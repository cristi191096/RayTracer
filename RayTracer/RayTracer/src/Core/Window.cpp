#include "pch.h"
#include "Window.h"



Window::Window(const WindowData & data)
{
	Init(data);
}

Window::~Window()
{
	//Shutdown();
}

void Window::SetInputCallbacks()
{
}

void Window::OnEvent(SDL_Event& event) 
{
	if (event.type == SDL_WINDOWEVENT)
	{
		switch (event.window.event)
		{
		case SDL_WINDOWEVENT_SHOWN:
			SDL_Log("Window %d shown", event.window.windowID);
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			SDL_Log("Window %d hidden", event.window.windowID);
			break;

			//Window minimized
		case SDL_WINDOWEVENT_MINIMIZED:
			m_Minimised = true;
			break;

			//Window maxized
		case SDL_WINDOWEVENT_MAXIMIZED:
			m_Minimised = false;
			break;

			//Window restored
		case SDL_WINDOWEVENT_RESTORED:
			m_Minimised = false;
			break;

		}

	}
	else if (event.type == SDL_KEYDOWN) 
	{
		if (event.key.keysym.sym == SDLK_ESCAPE) 
		{
			event.type = SDL_QUIT;
		}
	}
}

void Window::OnUpdate()
{
	

	SDL_UpdateWindowSurface(m_Window);
}

void Window::Init(const WindowData & data)
{
	m_Minimised = false;

	m_Data.Title =		data.Title;
	m_Data.X =			data.X;
	m_Data.Y =			data.Y;
	m_Data.Width =		data.Width;
	m_Data.Height =		data.Height;
	m_Data.Fullscreen = data.Fullscreen;

	INFO("Creating Window {0}: ({1}, {2})", data.Title, data.Width, data.Height);

	int flags = SDL_WINDOW_SHOWN;//SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE;
	/*if (m_Data.Fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	}*/

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		INFO("[SDL]: Successfully initialised!");
		m_Window = SDL_CreateWindow(m_Data.Title.c_str(), m_Data.X, m_Data.Y, m_Data.Width, m_Data.Height, flags);
	}
	else
	{
		ERROR("[SDL]: Error initialising-> {0}", SDL_GetError());
	}

}

void Window::Shutdown()
{
	if (m_Window != NULL)
	{
		SDL_DestroyWindow(m_Window);
	}


	SDL_Quit();
}
