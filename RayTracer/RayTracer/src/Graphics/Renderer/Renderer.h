#pragma once
#include "Graphics\Scene.h"

class Renderer {

public:
	Renderer() {};
	virtual ~Renderer() {};
	virtual void Submit(Scene* scene) = 0;
	virtual void Flush() = 0;

protected:
	Scene* m_Scene;
};