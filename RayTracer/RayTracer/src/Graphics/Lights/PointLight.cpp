#include "pch.h"
#include "PointLight.h"
#include "Graphics\Renderer\Ray.h"


PointLight::PointLight(glm::vec3 pos, const Colour & diffuseColour, const int& samples, const Colour & ambientColour, const Colour & specularColour) 
	: m_Position(pos), m_DiffuseColour(diffuseColour), m_AmbientColour(ambientColour), m_SpecularColour(specularColour), m_Samples(samples)
{
	m_Radius = 1.0f;
	m_Intensity = 1.0f;
	m_RadiusSquared = m_Radius * m_Radius;
	Kl = 2 / m_Radius;
	Kq = 1 / m_RadiusSquared;
	CalculateSamples(100);
}

PointLight::PointLight(glm::vec3 pos, const Colour & diffuseColour, const float & intensity, const int& samples, const float & radius, const Colour & ambientColour, const Colour & specularColour) 
	: m_Position(pos), m_Intensity(intensity), m_Radius(radius), m_DiffuseColour(diffuseColour), m_AmbientColour(ambientColour), m_SpecularColour(specularColour), m_Samples(samples)
{
	m_RadiusSquared = m_Radius * m_Radius;
	Kl = 2 / m_Radius;
	Kq = 1 / m_RadiusSquared;
	CalculateSamples(100);
}

PointLight::~PointLight()
{
}

void PointLight::CalculateSamples(const int& width)
{
	//int r = rand() % 100 + 1;
	if (m_Samples < 1) m_Samples = 1;
	m_SamplePositions.clear();
	int number = floor(sqrt(m_Samples));
	float cellsize = width / m_Samples;
	halfCellsize = round(cellsize / 2);
	glm::vec3 first = glm::vec3(m_Position.x - width / 2, m_Position.y, m_Position.z - width /2);
	for (int i = 0; i < number; i++) 
	{
		for (int j = 0; j < number; j++) {
			m_SamplePositions.push_back(glm::vec3(	m_Position.x + cellsize * i,
													m_Position.y,
													m_Position.z + cellsize * j
			));
		}
	}
}

