#pragma once
#include "Graphics\Primitives\Shape.h"
#include "Graphics\Primitives\BoundingBox.h"
#include "Utils/Loader.h"

class Mesh : public Shape
{
public:
	Mesh(const glm::vec3& position, const std::string& filePath);
	Mesh(const glm::vec3& position, const std::string& filePath, const Material& material);
	virtual inline void SetIndex(const int& index) override;
	//Mesh(const glm::vec3& position, const float& radius, const Colour& material);
	~Mesh();

	virtual bool Intersect(Ray& ray) override;

private:
	float m_MinMax[6]; //xMin, xMax, yMin, yMax, zMin, zMax
	Loader m_Loader;
	std::string m_FilePath;
	BoundingBox* m_BBox;

public:
	

};

