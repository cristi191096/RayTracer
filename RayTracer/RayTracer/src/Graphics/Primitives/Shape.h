#pragma once
#include "Graphics\Material.h"

class Ray;

/*
Virtual interface for all objects and primitives in the scene.
Should contain: position, material, distance to the camera (calculated in the scene)
Virtuals: Intersect, 
*/
class Shape {

public:
	Shape();
	Shape(const glm::vec3& position);
	Shape(const Material& material);
	Shape(const glm::vec3& position, const Material& material);
	Shape(const glm::vec3& position, const Colour& material);

	virtual ~Shape();

	inline void SetPosition(const glm::vec3& position) { m_Position = position; }
	inline const glm::vec3& GetPosition() const { return m_Position; }

	virtual inline void SetIndex(const int& index) { m_Index = index; }
	inline const int& GetIndex() const { return m_Index; }

	
	void SetMaterial(const Colour& colour,/* const Colour& ambient = Colour(0.2f, 0.2f, 0.2f, 1.0f),*/ const Colour& specular = Colour(1.0f, 1.0f, 1.0f, 1.0f));
	inline void SetMaterial(const Material& newMat) { m_Material = newMat; }
	inline const Material& GetMaterial() const { return m_Material; }

	inline const float& GetDistanceToCamera() const { return m_DistanceToCamera; }

	virtual bool Intersect(Ray& ray) = 0;

protected:
	Material m_Material;
	glm::vec3 m_Position;
	float m_DistanceToCamera;
	int m_Index = -1;
};