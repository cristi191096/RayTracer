#include "pch.h"
#include "Mesh.h"
#include "Graphics\Primitives\Triangle.h"

Mesh::Mesh(const glm::vec3 & position, const std::string& filePath) : Shape (position)

{
	std::vector<glm::vec3> vertices, normals;
	const float infinity = FLT_MAX;
	m_BBox = new BoundingBox(glm::vec3(0.0f), glm::vec3(0.0f));

	float minX =  infinity;
	float minY =  infinity;
	float minZ =  infinity;
	float maxX = -infinity;
	float maxY = -infinity;
	float maxZ = -infinity;
	if (!m_Loader.loadOBJ(filePath.c_str(), vertices, normals))
		ERROR("Could not load model located at {0}: ", filePath);

	for (int i = 0; i < vertices.size(); i+=3) {
		for (int j = 0; j < 3; j++) {
			if (minX > vertices[i + j].x)
				minX = vertices[i + j].x;
			if (minY > vertices[i + j].y)
				minY = vertices[i + j].y;
			if (minZ > vertices[i + j].z)
				minZ = vertices[i + j].z;
			if (maxX < vertices[i + j].x)
				maxX = vertices[i + j].x;
			if (maxY < vertices[i + j].y)
				maxY = vertices[i + j].y;
			if (maxZ < vertices[i + j].z)
				maxZ = vertices[i + j].z;
		}

		Triangle* t = new Triangle(vertices[i], vertices[i + 1], vertices[i + 2]);
		t->SetNormals(normals[i], normals[i + 1], normals[i + 2]);
		//t->SetIndex(this->m_Index);
		 m_BBox->m_Triangles.push_back(t);	
	}

	//	for (int i = 0; i < m_BBox->m_Triangles.size(); i++) {
	//	if (m_BBox->m_Triangles[i]->GetIndex() == -1) {
	//		m_BBox->m_Triangles[i]->SetIndex(this->m_Index);
	//	}
	//}
	m_BBox->SetMin(glm::vec3(m_Position.x + minX, m_Position.y + minY, m_Position.z + minZ));
	m_BBox->SetMax(glm::vec3(m_Position.x + maxX, m_Position.y + maxY, m_Position.z + maxZ));
	m_BBox->ComputeCentre();
	m_BBox->Split(0);
}

Mesh::Mesh(const glm::vec3 & position, const std::string& filePath, const Material& material) : Shape(position, material)
{
	std::vector<glm::vec3> vertices, normals;
	glm::vec3 min(0.0f,0.0f,0.0f);
	glm::vec3 max(0.0f,0.0f,0.0f);
	const float infinity = FLT_MAX;
	m_BBox = new BoundingBox(glm::vec3(0.0f), glm::vec3(0.0f));

	if (!m_Loader.loadOBJ(filePath.c_str(), vertices, normals))
		ERROR("Could not load model located at {0}: ", filePath);

	for (int i = 0; i < vertices.size(); i+=3) {
		for (int j = 0; j < 3; j++) {
			if (min.x > vertices[i + j].x)
				min.x = vertices[i + j].x;
			if (min.y > vertices[i + j].y)
				min.y = vertices[i + j].y;
			if (min.z > vertices[i + j].z)
				min.z = vertices[i + j].z;
			if (max.x < vertices[i + j].x)
				max.x = vertices[i + j].x;
			if (max.y < vertices[i + j].y)
				max.y = vertices[i + j].y;
			if (max.z < vertices[i + j].z)
				max.z = vertices[i + j].z;
		}

		Triangle* t = new Triangle(vertices[i] + m_Position, vertices[i + 1] + m_Position, vertices[i + 2] + m_Position, material);
		t->SetNormals(normals[i], normals[i + 1], normals[i + 2]);
		//t->SetIndex(this->m_Index);
		m_BBox->m_Triangles.push_back(t);	
	}
	INFO("Triangles: {0}", m_BBox->m_Triangles.size());
	m_BBox->SetMin(min);
	m_BBox->SetMax(max);
	m_BBox->ComputeCentre();
	m_BBox->SetMin(m_BBox->GetMin() + m_Position);
	m_BBox->SetMax(m_BBox->GetMax() + m_Position);
	m_BBox->SetCentre(m_BBox->GetCentre() + m_Position);
	m_BBox->Split(0);
	INFO("Octree built successfully!");
	//TRACE("MinMax: {0}, {1}, {2}, {3}, {4}, {5}",m_Position.x + minX, m_Position.y + minY,m_Position.z + minZ, m_Position.x + maxX, m_Position.y + maxY, m_Position.z + maxZ);
	//m_BBox = new BoundingBox(glm::vec3( m_MinMax[0], m_MinMax[2], m_MinMax[4]), glm::vec3( m_MinMax[1], m_MinMax[3], m_MinMax[5]));
}

void Mesh::SetIndex(const int& index)
{
	
	for (int i = 0; i < m_BBox->m_Triangles.size(); i++) {

		m_BBox->m_Triangles[i]->SetIndex(index);

	}
}

Mesh::~Mesh()
{
	//delete m_BBox;
}


bool Mesh::Intersect(Ray & ray)
{
	if (!m_BBox->Intersect(ray))
	{
		return false;
	}


	return true;
}
