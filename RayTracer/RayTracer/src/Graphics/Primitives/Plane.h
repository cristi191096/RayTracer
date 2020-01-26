#pragma once
#include "Graphics\Primitives\Shape.h"

class Plane : public Shape
{
public:
	Plane(const glm::vec3& position, const glm::vec3& normal = glm::vec3(0.0f, 1.0f, 0.0f));
	Plane(const glm::vec3& position, const Material& material, const glm::vec3& normal = glm::vec3(0.0f, 1.0f, 0.0f));
	//Plane(const glm::vec3& position, const float& radius, const Colour& material);
	~Plane();

	virtual bool Intersect(Ray& ray) override;

private:
	glm::vec3 m_Normal;
};
