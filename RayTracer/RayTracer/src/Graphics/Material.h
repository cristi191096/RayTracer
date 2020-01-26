#pragma once

typedef glm::vec4 Colour;

//union Color {
//
//};

struct Color {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

class Material
{
	
public:
	Material();
	Material(const Colour& colour, const Colour& specular = Colour(1.0f, 1.0f, 1.0f, 1.0f), float shininess = 128.0f);
	Material(const Colour& colour, const int& reflectionDepth, const Colour& specular = Colour(1.0f, 1.0f, 1.0f, 1.0f), float shininess = 128.0f);
	~Material();

	//Use Set Colour for converting the final colours to unsigned int
	void SetColour(const Colour& color); //main colour
	void SetAmbientColour(const Colour& color);
	void SetSpecularColour(const Colour& color);
	inline void SetShininess(const float& val) { m_Shininess = val; }

	inline const Colour& GetColour() const { return m_DiffuseColour; }
	inline const Colour& GetAmbientColour() const { return m_AmbientColour; }
	inline const Colour& GetSpecularColour() const { return m_SpecularColour; }
	inline const float& GetShininess() const { return m_Shininess; }
	inline const int& GetReflectionDepth() const { return m_ReflectionDepth; }

	/*inline const Colour& GetColour() const { return Colour(m)}*/

private:
	//		main colour		ambient			specular/shininess
	Colour m_DiffuseColour, m_AmbientColour, m_SpecularColour;   //Use this for passing the pixel information to SDL
	float m_Shininess = 128.0f;
	int m_ReflectionDepth;

};
