#pragma once

class RaytraceRenderer;

struct WindowData {

	std::string Title;
	unsigned int X;
	unsigned int Y;
	unsigned int Width;
	unsigned int Height;
	bool Fullscreen;

	WindowData(const std::string& title = "RayTracer",
		unsigned int posX = 70,
		unsigned int posY = 100,
		unsigned int width = 800,
		unsigned int height = 600,
		bool fullscreen = false)
		: Title(title), X(posX), Y(posY), Width(width), Height(height), Fullscreen(fullscreen)
	{
	}
};


class Window {

public:
	Window(const WindowData& data = WindowData());
	~Window();

	void SetInputCallbacks();
	void OnUpdate();
	void OnEvent(SDL_Event& event);

	inline unsigned int GetWidth() const { return m_Data.Width; };
	inline unsigned int GetHeight() const { return m_Data.Height; };
	inline bool IsMinimised() const { return m_Minimised; }
	void Shutdown();

private:
	bool m_Minimised;	//Used for rendering only when the window is visible
	WindowData m_Data;
	SDL_Window *m_Window;

	void Init(const WindowData& data);
	

	friend class RaytraceRenderer;
};