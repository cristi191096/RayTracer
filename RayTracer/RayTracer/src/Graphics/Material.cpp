#include "pch.h"
#include "Material.h"

Material::Material()
{
	SetColour(Colour(1.0f, 1.0f, 1.0f, 1.0f));			//Default white
	SetAmbientColour(Colour(1.0f, 1.0f, 1.0f, 1.0f));
	SetSpecularColour(Colour(1.0f, 1.0f, 1.0f, 1.0f));
}
Material::Material(const Colour & colour, const Colour & specular, float shininess)
	:m_Shininess(shininess), m_ReflectionDepth(0)
{
	SetColour(colour);
	SetAmbientColour(colour);
	SetSpecularColour(specular);
}

Material::Material(const Colour & colour, const int& reflectionDepth, const Colour & specular, float shininess)
	: m_ReflectionDepth(reflectionDepth), m_Shininess(shininess)
{
	SetColour(colour);
	SetAmbientColour(colour);
	SetSpecularColour(specular);
}

Material::~Material()
{
}

void Material::SetColour(const Colour & color)
{
	/*unsigned int r = (unsigned int)(color.x * 255.0f);
	unsigned int g = (unsigned int)(  color.y * 255.0f);
	unsigned int b = (unsigned int)(  color.z * 255.0f);
	unsigned int a = (unsigned int)(  color.w * 255.0f);

	m_DiffuseColour = a << 24 | b << 16 | g << 8 | r;*/

	/*if (color.r > 1.0f || color.g > 1.0f || color.b > 1.0f || color.a > 1.0f) {
		WARN("Diffuse Colour( {0}, {1}, {2}, {3}) has values greater than 1. Colours should be between 0 and 1.", color.r, color.g, color.b, color.a);
		m_DiffuseColour.r = 255;
		m_DiffuseColour.g = 255;
		m_DiffuseColour.b = 0;
		m_DiffuseColour.a = 255;
	}
	else
	{
		m_DiffuseColour.r = (Uint8)(color.x * 255);
		m_DiffuseColour.g = (Uint8)(color.y * 255);
		m_DiffuseColour.b = (Uint8)(color.z * 255);
		m_DiffuseColour.a = (Uint8)(color.w * 255);
	}*/

	m_DiffuseColour = glm::clamp(color,Colour(0.0f, 0.0f, 0.0f, 0.0f), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	
}

//Don't bother setting the alpha channel. It's 1 anyway
void Material::SetAmbientColour(const Colour & color)
{
	//unsigned int r = (unsigned int)(color.x * 255.0f);
	//unsigned int g = (unsigned int)(color.y * 255.0f);
	//unsigned int b = (unsigned int)(color.z * 255.0f);
	//unsigned int a = (unsigned int)(1 * 255.0f);

	//m_AmbientColour = a << 24 | b << 16 | g << 8 | r;
	m_AmbientColour = glm::clamp(color,Colour(0.0f, 0.0f, 0.0f, 0.0f), Colour(1.0f, 1.0f, 1.0f, 1.0f));
}

//Don't bother setting the alpha channel. It's 1 anyway
void Material::SetSpecularColour(const Colour & color)
{
	/*unsigned int r = (unsigned int)(color.x * 255.0f);
	unsigned int g = (unsigned int)(color.y * 255.0f);
	unsigned int b = (unsigned int)(color.z * 255.0f);
	unsigned int a = (unsigned int)(1 * 255.0f);

	m_SpecularColour = a << 24 | b << 16 | g << 8 | r;*/

	m_SpecularColour = glm::clamp(color,Colour(0.0f, 0.0f, 0.0f, 0.0f), Colour(1.0f, 1.0f, 1.0f, 1.0f));
}
