#pragma once
typedef glm::vec4 Colour;

class PointLight
{
public:
	float Kc = 1.0f;
	float Kl = 0.09f;
	float Kq = 0.032f;
	float m_Radius, m_Intensity;
	int halfCellsize;
	glm::vec3 m_Position;
	std::vector<glm::vec3> m_SamplePositions;

public:
	PointLight(glm::vec3 pos, const Colour& diffuseColour, const int& samples = 1, const Colour& ambientColour = Colour(0.2f, 0.2f, 0.2f, 0.2f), const Colour& specularColour = Colour(1.0f, 1.0f, 1.0f, 1.0f));
	PointLight(glm::vec3 pos, const Colour& diffuseColour, const float& intensity, const int& samples = 1, const float& radius = 2.0f, const Colour& ambientColour = Colour(0.2f, 0.2f, 0.2f, 0.2f), const Colour& specularColour = Colour(1.0f, 1.0f, 1.0f, 1.0f));
	//PointLight(glm::vec3 pos, const Colour& diffuseColour, const float& intensity,  const float& radius = 2.0f, const Colour& ambientColour = Colour(0.2f, 0.2f, 0.2f, 0.2f), const Colour& specularColour = Colour(1.0f, 1.0f, 1.0f, 1.0f));
	~PointLight();

	inline const glm::vec3& GetDirection() const { return glm::normalize(m_Direction); }
	inline void SetDirection(const glm::vec3& direction) { m_Direction = direction; }

	inline void SetPosition(const glm::vec3& position) { m_Position = position; }
	inline const glm::vec3& GetPosition() const { return m_Position; }

	inline const Colour& GetColour() const { return m_DiffuseColour; }
	inline void SetColour(const Colour& col) { m_DiffuseColour = col; }

	inline const Colour& GetAmbientColour() const { return m_AmbientColour; }
	inline void SetAmbientColour(const Colour& col) { m_AmbientColour = col; }

	inline const Colour& GetSpecularColour() const { return m_SpecularColour; }
	inline void SetSpecularColour(const Colour& col) { m_SpecularColour = col; }

	inline const float& GetRadius() const { return m_Radius; }
	inline void SetRadius(const float& radius) { m_Radius = radius; }

	//Set the number of samples for soft shadow
	inline void SetSamples(const int& value) { m_Samples = value; }
	inline const int& GetSamples() const { return m_Samples; }
	void CalculateSamples(const int& width);

	inline const float& GetIntensity() const { return m_Intensity; }
	inline void SetIntensity(const float& intensity) { m_Intensity = intensity; }

	//Colour CalculateColour(Ray& ray);

private:
	float m_RadiusSquared;
	int m_Samples;

	
	glm::vec3 m_Direction;
	Colour m_DiffuseColour, m_AmbientColour, m_SpecularColour;
};