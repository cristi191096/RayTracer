#pragma once
#include "Graphics\Renderer\Ray.h"
#include "Graphics\Primitives\Triangle.h"

#define MAX_TRIANGLES_PER_BOX	45
#define MAX_DEPTH				5
#define NUMBER_OF_CHILDREN		8

class BoundingBox {


public:
	std::vector<Triangle*> m_Triangles;	
	
public:
	BoundingBox(glm::vec3 min, glm::vec3 max);
	inline void SetMin(glm::vec3 min) { m_Params[0] = min; }
	inline void SetMax(glm::vec3 max) { m_Params[1] = max; }
	inline void ComputeCentre() { m_Centre = (m_Params[1] + m_Params[0]) * 0.5f; }
	inline void SetCentre(glm::vec3 centre) { m_Centre = centre; }
	~BoundingBox();
	void Split(int level); //check self number of triangles -> if greater than Max no. allowed -> make other children. 
	bool Intersect(Ray& ray);

	inline glm::vec3 GetMin() { return m_Params[0]; }
	inline glm::vec3 GetMax() { return m_Params[1]; }
	inline glm::vec3 GetCentre() { return m_Centre; }

private:
	bool isLeaf = false;
	glm::vec3 m_Params[2];
	glm::vec3 m_Centre;
	const float m_Epsilon = 0.001f;
	std::vector< BoundingBox*> children;
	//BoundingBox* parent;
	//static int totalTriangles;

private:
	void swap(float& first, float& second);
	void Add(Triangle* t);
	bool IsVertexInside(const glm::vec3& vert);


};