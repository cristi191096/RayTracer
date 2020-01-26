#include "pch.h"
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::vec3 & direction)
	: m_Direction(direction)
{
	m_DiffuseColour = Colour(1.0f, 1.0f, 1.0f, 1.0f);
	m_AmbientColour = Colour(0.2f, 0.2f, 0.2f, 0.2f);
	m_SpecularColour = Colour(1.0f, 1.0f, 1.0f, 1.0f);
}

DirectionalLight::DirectionalLight(const glm::vec3 & direction, const Colour & diffuseColour, const Colour& ambientColour, const Colour& specularColour)
	: m_Direction(direction), m_DiffuseColour(diffuseColour), m_AmbientColour(ambientColour), m_SpecularColour(specularColour)
{
}
