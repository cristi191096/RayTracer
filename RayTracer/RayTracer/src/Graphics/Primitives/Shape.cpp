#include "pch.h"
#include "Shape.h"

Shape::Shape()		//Used for triangles
{
	m_Position = glm::vec3(0, 0, 0);
	m_Material = Material(Colour(1.0f, 0.0f, 1.0f, 1.0f)); // Magenta if NULL
}

Shape::Shape(const glm::vec3& position)
	: m_Position(position)
{
		//m_Material = Material(Colour(1.0f, 0.0f, 1.0f, 1.0f)); // Magenta if NULL
	
}

Shape::Shape(const Material & material)
	: m_Material(material)
{
	
}

Shape::Shape(const glm::vec3 & position, const Material & material)
	: m_Position(position), m_Material(material)
{
	
}

Shape::Shape(const glm::vec3 & position, const Colour & material)
{
	SetMaterial(material);
	//m_Material = new Material(material);
}

Shape::~Shape()
{
	//if (m_Material != nullptr)
	//	delete m_Material;
	//
	//m_Material = nullptr;
}

void Shape::SetMaterial(const Colour & colour, /*const Colour & ambient,*/ const Colour & specular)
{
	m_Material = Material(colour, /*ambient,*/ specular);
}