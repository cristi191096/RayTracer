#include "pch.h"
#include "Scene.h"


Scene::Scene(Camera* camera)
	: m_Camera(camera)
{
//	m_DirectionalLight = DirectionalLight(glm::vec3(-0.5f, -0.5f, 0.0f));
}

Scene::~Scene()
{
	delete m_Camera;
	for (Shape* shape : m_Shapes)
		delete shape;
}

void Scene::Add(Shape * obj)
{
		m_Shapes.push_back(obj);
		m_Materials.push_back(obj->GetMaterial());
		obj->SetIndex(m_ObjectsCount++);

		//WARN("Shape Index: {0}", obj->GetIndex());

}



void Scene::Add(const PointLight & light)
{
	m_PointLights.push_back(light);
}

void Scene::RemoveLastObject()
{
	m_Shapes.pop_back();
	m_ObjectsCount--;
}
