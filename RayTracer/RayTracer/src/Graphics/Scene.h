#pragma once
#include "Graphics\Primitives\Shape.h"
#include "Graphics\Primitives\Mesh.h"
#include "Graphics\Cameras\Camera.h"
#include "Graphics\Lights\DirectionalLight.h"
#include "Graphics\Lights\PointLight.h"


class Scene {

public:
	bool reflectionsON;
	bool jitterON = true;
	Scene(Camera* camera);
	~Scene();

	void Add(Shape* obj);
	void Add(const PointLight& light);
	void RemoveLastObject();
	inline const int& GetObjectCount() const { return m_ObjectsCount; }
	inline const std::vector<Shape*>& GetObjects() const { return m_Shapes; }
	inline const std::vector<Material>& GetMaterials() const { return m_Materials; }

	inline void SetCamera(Camera* camera) { m_Camera = camera; }
	inline Camera* GetCamera() const { return m_Camera; }

	inline const DirectionalLight& GetDirectionalLight() const { return m_DirectionalLight; }
	inline std::vector<PointLight>& GetPointLights() { return m_PointLights; }

private:
	Camera* m_Camera;
	DirectionalLight m_DirectionalLight = DirectionalLight(glm::vec3(-0.5f, -1.0f, -0.2f));
	std::vector<Shape*> m_Shapes;
	std::vector<Material> m_Materials;
	std::vector<PointLight> m_PointLights;
	int m_ObjectsCount = 0;
};