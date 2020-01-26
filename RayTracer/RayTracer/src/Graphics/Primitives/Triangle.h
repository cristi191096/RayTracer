#pragma once
#include "Graphics\Primitives\Shape.h"

class Triangle : public Shape
{
public:
	Triangle(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C);
	Triangle(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const Material& material);// , const glm::vec3& normal = glm::vec3(0.0f, 1.0f, 0.0f));
	//Triangle(const glm::vec3& position, const float& radius, const Colour& material);

	void SetPosition(glm::vec3 pos);
	void SetNormals(const glm::vec3& An, const glm::vec3& Bn, const glm::vec3& Cn);
	inline const glm::vec3& A() const { return m_A; }
	inline const glm::vec3& B() const { return m_B; }
	inline const glm::vec3& C() const { return m_C; }
	~Triangle();

	virtual bool Intersect(Ray& ray) override;

private:
	glm::vec3 m_A, m_B, m_C;
	glm::vec3 m_ANormal, m_BNormal, m_CNormal;
	glm::vec3 AB;
	glm::vec3 AC;
	
};
