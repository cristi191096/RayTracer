#include "pch.h"
#include "GameLayer.h"
#include "Graphics\Renderer\RaytraceRenderer.h"
#include "Core\Window.h"
#include "Graphics\Scene.h"
#include "Graphics\Cameras\Camera.h"
#include "Graphics\Primitives\Sphere.h"
#include "Graphics\Primitives\Plane.h"
#include "Graphics\Primitives\Triangle.h"
#include "Graphics\Primitives\Mesh.h"
#include "Graphics\Renderer\RaytraceRenderer.h"
#include "Graphics\Lights\PointLight.h"


using Time = std::chrono::high_resolution_clock;
using fsec = std::chrono::duration<float>;



GameLayer::GameLayer() : Layer("GameLayer")
{
}



GameLayer::~GameLayer()
{
	//delete m_Renderer;
	//m_Renderer = nullptr;
	//delete m_Scene;
	//m_Scene = nullptr;
}

void GameLayer::OnAttach()
{
	m_Timer.start();
	m_Renderer = new RaytraceRenderer();
	m_Scene = new Scene(new Camera());

	PointLight light = PointLight(glm::vec3(1.0f, 5.0f, -6.0f), Colour(1.0f, 1.0f, 1.0f, 1.0f), 1.5f, 20, 5.0f);


	//====================Materials==================================
	Material yellow = Material(Colour(1.0f, 1.0f, 0.0f, 1.0f),3);
	Material red = Material(Colour(1.0f, 0.0f, 0.0f, 1.0f),3);
	red.SetShininess(128.0f);
	Material white = Material(Colour(1.0f, 1.0f, 1.0f, 1.0f),0);
	Material black = Material(Colour(0.0f, 0.0f, 0.0f, 1.0f));
	Material green = Material(Colour(0.0f, 1.0f, 0.0f, 1.0f));
	Material greenMatte = Material(Colour(0.0f, 1.0f, 0.0f, 1.0f), 0, Colour(0.7f, 0.7f, 0.7f, 1.0f));
	greenMatte.SetShininess(1.0f);
	Material maroon = Material(Colour(0.5f, 0.5f, 0.5f, 1.0f),5);
	Material jade = Material(Colour(0.54f, 0.89f, 0.63f, 1.0f), 0, Colour(0.31f, 0.31f, 0.31f, 1.0f), 128.0f);
	Material blueemarald = Material(Colour(0.37f, 0.37f, 0.61f, 1.0f), 0, Colour(0.63f, 0.72f, 0.63f, 1.0f), 0.6f * 128.0f);
	//Material greenRef = Material(Colour(0.0f, 1.0f, 0.0f, 1.0f), 0);
	//========================================================================
	

//	Triangle* t = new Triangle(glm::vec3(-2, 0, -3), glm::vec3(-1, 1, -3), glm::vec3(0, 1, -3), yellow);
////	Mesh* cube = new Mesh(glm::vec3(-2, 1, -4), "src/res/cube_simple.obj", green);
	//Mesh* teapot = new Mesh(glm::vec3(0, 0.1f, -10), "src/res/teapot_simple.obj", greenMatte);
//
//
	m_Scene->Add(new Sphere(glm::vec3(-2.5f, 1.0f, -10.0f), 1.5f, red));
	m_Scene->Add(new Sphere(glm::vec3(-7.0f, 0.5f, -12.0f), 1.0f, white));
	m_Scene->Add(new Sphere(glm::vec3(7.0f, 0.5f, -12.0f), 1.0f, maroon));
	m_Scene->Add(new Plane(glm::vec3(-10.0f, -1.0f, -13.0f), greenMatte, glm::vec3(0.0f, 1.0f, 0.0f)));
	m_Scene->Add(light);
//	m_Scene->Add(PointLight(glm::vec3(-10, 10, -5), Colour(1.0f, 1.0f, 1.0f, 1.0f), 1.5f, 90, 5.0f));
	//m_Scene->Add(PointLight(glm::vec3(5, 10, -5), Colour(0.0f, 0.0f, 1.0f, 1.0f), 1.5f, 1, 5.0f));
	//m_Scene->Add(PointLight(glm::vec3(-5, 10, -5), Colour(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 3.0f));
	//m_Scene->Add(PointLight(glm::vec3(10, 10, 5), Colour(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 3.0f));
	//m_Scene->Add(PointLight(glm::vec3(-10, 10, 5), Colour(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 3.0f));
	//m_Scene->Add(PointLight(glm::vec3(-5, 10, 5), Colour(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 3.0f));
	//m_Scene->Add(PointLight(glm::vec3(5, 10, 5), Colour(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 3.0f));

	

	m_Scene->Add(new Mesh(glm::vec3(5.0f, 1.0f, -10.0f), "src/res/teapot_smooth.obj", blueemarald));



	m_Renderer->Submit(m_Scene);

}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate()
{
	

	//float avgFPS = m_Frames / (m_Timer.getTicks() / 1000.f);
	//if (avgFPS > 2000000)
	//{
	//	avgFPS = 0;
	//}

	
	if (m_KeyPressed) {
		auto start = Time::now();
		m_Renderer->Flush();
		m_KeyPressed = false;

		auto end = Time::now();
		fsec duration = end - start;
		if (displayTime) {
			INFO("Time: {0}", duration.count());
		}
	}
}

void GameLayer::OnEvent(SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN)
	{
		m_KeyPressed = true;
		m_Scene->GetCamera()->OnEvent(event);

		if (event.key.keysym.sym == SDLK_h) {
			m_Scene->jitterON = false;
			m_Scene->GetPointLights()[0].SetSamples(0);
			m_Scene->GetPointLights()[0].CalculateSamples(100);
			//TRACE("Light Position: {0}, {1}, {2}", m_Scene->GetPointLights()[0].m_Position.x, m_Scene->GetPointLights()[0].m_Position.y, m_Scene->GetPointLights()[0].m_Position.z);
		}
		if (event.key.keysym.sym == SDLK_s) {
			int s = m_Scene->GetPointLights()[0].GetSamples();
			if (m_Scene->GetPointLights()[0].GetSamples() < 90) {
				m_Scene->GetPointLights()[0].SetSamples( s += 10);
				m_Scene->GetPointLights()[0].CalculateSamples(100);
				INFO("Samples are now: {0}", m_Scene->GetPointLights()[0].GetSamples());
			}
			else
			{
				ERROR("WOAH, {0}? Please, don't kill me!", m_Scene->GetPointLights()[0].GetSamples());
			}
		}
		if (event.key.keysym.sym == SDLK_LEFTBRACKET) {
			m_Scene->GetPointLights()[0].m_Intensity -= 0.25f;
			//TRACE("Light Position: {0}, {1}, {2}", m_Scene->GetPointLights()[0].m_Position.x, m_Scene->GetPointLights()[0].m_Position.y, m_Scene->GetPointLights()[0].m_Position.z);
		}
		if (event.key.keysym.sym == SDLK_RIGHTBRACKET) {
			m_Scene->GetPointLights()[0].m_Intensity += 0.25f;

			//TRACE("Light Position: {0}, {1}, {2}", m_Scene->GetPointLights()[0].m_Position.x, m_Scene->GetPointLights()[0].m_Position.y, m_Scene->GetPointLights()[0].m_Position.z);
		}
		if (event.key.keysym.sym == SDLK_r) {
			m_Scene->reflectionsON = m_Scene->reflectionsON ? false : true;
		}
		if (event.key.keysym.sym == SDLK_j) {
			m_Scene->jitterON = m_Scene->jitterON ? false : true;
		}
			if (event.key.keysym.sym == SDLK_SPACE) {
			displayTime = displayTime ? false : true;
		}
		//if (event.key.keysym.sym == SDLK_1) {
		//	if (!teapotON) {
		//		m_Scene->Add( new Mesh(glm::vec3(3,1, -10), "src/res/teapot_simple.obj",  Material(Colour(0.0f, 1.0f, 0.0f, 1.0f), 0, Colour(0.7f, 0.7f, 0.7f, 1.0f))));
		//		teapotON = true;
		//	}
		//	else
		//	{
		//		m_Scene->RemoveLastObject();
		//		teapotON = false;
		//	}
		//}

	}
	if (event.type == SDL_KEYUP) 
	{
		m_Scene->GetCamera()->m_CameraMoved = true;
		//m_Scene->GetCamera()->OnEventFinished(event);
	}
}


