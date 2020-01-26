#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

class Application {

public:
	Application();
	virtual ~Application();

	void Run();
	void PushLayer(Layer* layer);
	void PushOverlay(Layer* layer);

	inline static Application& Get() { return *s_Instance; }
	inline Window& GetWindow() { return *m_Window; }


	void OnEvent(/*Event& e*/);

	

private:
	LayerStack m_LayerStack;
	static Application* s_Instance;
	std::unique_ptr<Window> m_Window;
	bool m_Running;

	void Init();
	void PrintOptions();

};

Application* CreateApplication();