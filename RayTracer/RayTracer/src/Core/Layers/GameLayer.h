#pragma once
#include "Core\Layer.h"
#include "Utils\Timer.h"


class Scene;


class GameLayer : public Layer 
{
public: 
	GameLayer();
	GameLayer(const WindowData& windowData);
	~GameLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnEvent(SDL_Event& event) override;

private:
	bool m_KeyPressed = true;
	bool teapotON = false;
	bool displayTime = false;
	int m_Frames = 0;
	Scene* m_Scene;
	Timer m_Timer;
};