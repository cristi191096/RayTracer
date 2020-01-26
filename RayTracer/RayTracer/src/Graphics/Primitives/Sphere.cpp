#include "pch.h"
#include "Sphere.h"
#include "Graphics\Renderer\Ray.h"

Sphere::Sphere(const glm::vec3& position, const float& radius) : Shape(position),
	 m_Radius(radius)
{
	m_RadiusSquared = m_Radius * m_Radius;
}




Sphere::Sphere(const glm::vec3 & position, const float& radius, const Material& material) : Shape(position, material),
	m_Radius(radius)
{
	m_RadiusSquared = m_Radius * m_Radius;
}

//Sphere::Sphere(const glm::vec3 & position, const float& radius, const Colour & material) : Shape(position, material),
//	m_Radius(radius)
//{
//	m_RadiusSquared = m_Radius * m_Radius;
//}

Sphere::~Sphere()
{
	
}

bool Sphere::Intersect(Ray & ray)
{

	glm::vec3 I = m_Position - ray.Origin;
	float Tca = glm::dot(I, ray.Direction);

	//TRACE("Pixel No: {0}", ray.pixelNo);

	float IlengthSquared = glm::dot(I, I);
	//float Tca = glm::dot(I, rayDir);

	if (Tca < 0) {
		return false;
	}

	float sSquared = IlengthSquared - Tca*Tca;


	if (sSquared > m_RadiusSquared)
	{
		return false;
	}

	float Thc = sqrt(m_RadiusSquared - sSquared);
	float T0 = Tca - Thc;
	float T1 = Tca + Thc;
	//if (!ray.towardsLight) {
		if (ray.hitInfo.distanceToOrigin == 0.0f || ray.hitInfo.distanceToOrigin > T0) {

			ray.hitInfo.intersectionPoint = ray.Origin + (Tca - Thc)*ray.Direction;
			ray.hitInfo.normal = glm::normalize(ray.hitInfo.intersectionPoint - m_Position);
			ray.hitInfo.shapeIndex = m_Index;
			ray.hitInfo.distanceToOrigin = T0;
		}

	//}
	//else
	//{

	//}
		return true;
	
}
