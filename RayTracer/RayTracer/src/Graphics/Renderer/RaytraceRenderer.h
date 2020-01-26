#pragma once
#include "Graphics\Renderer\Renderer.h"
#include "Graphics\Renderer\Ray.h"


class RaytraceRenderer : public Renderer
{

public:
	RaytraceRenderer();
	~RaytraceRenderer();

	virtual void Submit(Scene* scene) override;
	virtual void Flush() override;

private:
	//TODO: Get the hit information
	glm::vec3 m_NormalisedRayDirection;
	unsigned int m_Width, m_Height;
	//std::vector<Ray> m_Rays; //Should be pixels and one ray
	SDL_Surface* m_windowSurface;
	SDL_Surface* m_renderSurface;
	float m_AspectRatio, m_TanFOV; // TanFOV = tan(FOV/2)
	std::vector<Material> m_Materials;
	
	void CheckRayHits(Ray& ray);
	Colour CalculateDirectionalLight(const Ray& ray);
	Colour CalculatePointLight(const PointLight& light, const Material& object, glm::vec3& lightDir,const Hit& hitObject, const float& cutoff);
	Colour CalculateColour(Ray ray, const int& rayDepth);
	void Init();
	void Render(const int& startW, const int& endW);
	float GeneratRandom(int min, int max);
	//void SetPixels(int x, int y, )
};