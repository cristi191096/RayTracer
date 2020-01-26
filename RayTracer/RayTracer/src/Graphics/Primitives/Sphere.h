#pragma once
#include "Graphics\Primitives\Shape.h"

class Sphere : public Shape
{
public:
	Sphere(const glm::vec3& position, const float& radius = 2.0f);
	Sphere(const glm::vec3& position, const float& radius, const Material& material);
	//Sphere(const glm::vec3& position, const float& radius, const Colour& material);	//Currently not working
	~Sphere();

	virtual bool Intersect(Ray& ray) override;

private:
	float m_Radius;
	float m_RadiusSquared;
};

