#pragma once
typedef glm::vec4 Colour;

class DirectionalLight {

public:
	DirectionalLight(const glm::vec3& direction);
	DirectionalLight(const glm::vec3& direction, const Colour& diffuseColour, const Colour& ambientColour = Colour(0.2f, 0.2f, 0.2f, 0.2f), const Colour& specularColour = Colour(1.0f, 1.0f, 1.0f, 1.0f));

	inline const glm::vec3& GetDirection() const { return glm::normalize(m_Direction); }
	inline void SetDirection(const glm::vec3& direction) { m_Direction = direction; }

	inline const Colour& GetColour() const { return m_DiffuseColour; }
	inline void SetColour(const Colour& col) { m_DiffuseColour = col; }

	inline const Colour& GetAmbientColour() const { return m_AmbientColour; }
	inline void SetAmbientColour(const Colour& col) { m_AmbientColour = col; }

	inline const Colour& GetSpecularColour() const { return m_SpecularColour; }
	inline void SetSpecularColour(const Colour& col) { m_SpecularColour = col; }

private:
	glm::vec3 m_Direction;
	//glm::vec3 m_Position;
	Colour m_DiffuseColour, m_AmbientColour, m_SpecularColour;
};