#include "pch.h"
#include "Plane.h"
#include "Graphics\Renderer\Ray.h"

Plane::Plane(const glm::vec3 & position, const glm::vec3& normal) : Shape(position)
{
	m_Normal = glm::clamp(glm::vec3(0,0,0), glm::vec3(1.0f, 1.0f, 1.0f), normal);
}

Plane::Plane(const glm::vec3 & position, const Material& material, const glm::vec3& normal) : Shape(position, material)
{
	m_Normal = glm::clamp(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), normal);
	m_Normal.y *= -1;
}

Plane::~Plane()
{
}

bool Plane::Intersect(Ray & ray)
{

	float denominator = glm::dot(m_Normal, ray.Direction);

	if (denominator < 0.000001f)
		return false;

	float t = glm::dot((m_Position - ray.Origin),m_Normal) / denominator;

	if (t < 0.000001f)
		return false;

	if (ray.hitInfo.distanceToOrigin == 0.0f || ray.hitInfo.distanceToOrigin > t) {
		if (!ray.towardsLight) {
			ray.hitInfo.intersectionPoint = ray.Origin + t*ray.Direction;
			ray.hitInfo.normal = glm::normalize(m_Normal);
			ray.hitInfo.shapeIndex = m_Index;
			ray.hitInfo.distanceToOrigin = t;
		}
	}

	return true;
}
