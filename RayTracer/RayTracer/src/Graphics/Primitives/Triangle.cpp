#include "pch.h"
#include "Triangle.h"
#include "Graphics\Renderer\Ray.h"

#define CULLING 0		// PLEASE!!! I beg you! Use CULLING !!


Triangle::Triangle(const glm::vec3 & A, const glm::vec3 & B, const glm::vec3 & C)
	: m_A(A), m_B(B), m_C(C)
{
	//m_Position = C - (B - A);
	AB = m_B - m_A;
	AC = m_C - m_A;
}

Triangle::Triangle(const glm::vec3 & A, const glm::vec3 & B, const glm::vec3 & C, const Material& material) : Shape(material),
	m_A(A), m_B(B), m_C(C)
{
	//m_Position = C - (B - A);

	AB = m_B - m_A;
	AC = m_C - m_A;
}



void Triangle::SetPosition(glm::vec3 pos)
{
	m_A += pos;
	m_B += pos;
	m_C += pos;
}

void Triangle::SetNormals(const glm::vec3 & An, const glm::vec3 & Bn, const glm::vec3 & Cn)
{
	m_ANormal = An;
	m_BNormal = Bn;
	m_CNormal = Cn;
}

Triangle::~Triangle()
{
}

bool Triangle::Intersect(Ray & ray)
{
	glm::vec3 pvec = glm::cross(ray.Direction, AC);
	float det = glm::dot(AB, pvec);

#ifdef CULLING
	if (det < 0.00001f) return false;

#else
	if (fabs(det) < 0.00001f) return false;
#endif // CULLING
	float invDet = 1 / det;

	glm::vec3 tvec = ray.Origin - m_A;
	float u = glm::dot( tvec,pvec) * invDet;
	if (u < 0 || u > 1) return false;

	//add normals, based on uvw weights

	glm::vec3 qvec = glm::cross(tvec,AB);
	float v = glm::dot(ray.Direction, qvec) * invDet;
	if (v < 0 || u + v > 1) return false;

	float w = 1 - u - v;

	float t = glm::dot(AC, qvec) * invDet;
	//if (t <= 0) {
	//	return false;
	//}

	if (ray.hitInfo.distanceToOrigin == 0.0f || ray.hitInfo.distanceToOrigin > t) {
		ray.hitInfo.intersectionPoint = ray.Origin + t*ray.Direction;
		ray.hitInfo.normal = glm::normalize(((1 - u - v)*m_ANormal + u * m_BNormal + v * m_CNormal));
		ray.hitInfo.shapeIndex = m_Index;
		ray.hitInfo.distanceToOrigin = t;
		ray.hitInfo.intersectionPoint += ray.hitInfo.normal * 0.0001f;
		if (ray.towardsLight) {
			
		}
	}

	return true;
}
