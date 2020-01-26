#include "pch.h"
#include "RaytraceRenderer.h"
#include "Core\Application.h"


RaytraceRenderer::RaytraceRenderer()
{
	Init();
}

RaytraceRenderer::~RaytraceRenderer()
{
	delete m_Scene;
	delete m_windowSurface;
	delete m_renderSurface;
}

void RaytraceRenderer::Submit(Scene * scene)
{
	m_Scene = scene;
	m_AspectRatio = m_Scene->GetCamera()->GetAspectRation();
	m_TanFOV = glm::tan(glm::radians(m_Scene->GetCamera()->GetFieldOfView()) / 2);
	
	m_Materials = m_Scene->GetMaterials();

	unsigned int c = std::thread::hardware_concurrency();


}

/*SDL Surface 
surface->pixels = pixels
*/


void RaytraceRenderer::Flush()
{
	
	//Render(0, 800);
	std::thread t1(&RaytraceRenderer::Render, this ,0, 100);
	std::thread t2(&RaytraceRenderer::Render, this ,100, 200);
	std::thread t3(&RaytraceRenderer::Render, this ,200, 300);
	std::thread t4(&RaytraceRenderer::Render, this ,300, 400);
	std::thread t5(&RaytraceRenderer::Render, this ,400, 500);
	std::thread t6(&RaytraceRenderer::Render, this ,500, 600);
	std::thread t7(&RaytraceRenderer::Render, this ,600, 700);
	std::thread t8(&RaytraceRenderer::Render, this ,700, 800);
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();

	SDL_BlitSurface(m_renderSurface, nullptr, m_windowSurface, nullptr);

	m_Scene->GetCamera()->m_CameraMoved = false;
}

void RaytraceRenderer::Render(const int& startW, const int&  endW)
{
	Uint32* pixels = (Uint32*)m_renderSurface->pixels;


	for (int y = 0; y < m_Height; ++y)
	{
		for (int x = startW; x < endW; ++x)
		{

			double pixelNormalizedX = (x + 0.5f) / m_Width;
			double pixelNormalizedY = (y + 0.5f) / m_Height;

			double pixelRemappedX = (2 * pixelNormalizedX - 1)*m_AspectRatio;
			double pixelRemappedY = 1 - 2 * pixelNormalizedY;

			double pixelCameraX = pixelRemappedX * m_TanFOV;
			double pixelCameraY = pixelRemappedY * m_TanFOV;

			glm::vec3 m_CameraSpace = glm::vec3(pixelCameraX, pixelCameraY, -1);

			m_NormalisedRayDirection = glm::normalize(m_CameraSpace - m_Scene->GetCamera()->GetPosition());
			Ray ray(m_Scene->GetCamera()->GetPosition(), m_NormalisedRayDirection);

			CheckRayHits(ray);
			if (ray.hitInfo.shapeIndex != -1)
			{

				//unsigned int* offset = (unsigned int*)malloc(sizeof(unsigned int));
				int offset = y * (m_renderSurface->pitch / sizeof(Uint32)) + x;
				Colour colour = CalculateColour(ray, m_Materials[ray.hitInfo.shapeIndex].GetReflectionDepth());


					//WARN("Colour: R {0}, G {1}, B {2}", (Uint8)colour.r, (Uint8)colour.g, (Uint8)colour.b);
				*(pixels + offset) = SDL_MapRGB(m_renderSurface->format, (Uint8)glm::clamp((colour.r * 255), 0.0f, 255.0f), (Uint8)glm::clamp((colour.g * 255), 0.0f, 255.0f), (Uint8)glm::clamp((colour.b * 255), 0.0f, 255.0f));
			}
			else
			{
				//Clear colour
				int offset = (y * (m_renderSurface->pitch / sizeof(Uint32)) + x);
				*(pixels + offset) = SDL_MapRGB(m_renderSurface->format, 0, 0, 0);
			}
		}
	}
}


void RaytraceRenderer::CheckRayHits(Ray& ray)
{
	for (int i = 0; i < m_Scene->GetObjectCount(); i++) {
		if (m_Scene->GetObjects()[i]->Intersect(ray)) {
		
			//WARN("Ray object intersection");
		}
	}
}

Colour RaytraceRenderer::CalculateColour(Ray ray, const int& rayDepth) {
	Colour colour(0.0f, 0.0f, 0.0f, 0.0f);
	
	if (m_Scene->GetCamera()->m_CameraMoved) {
		for (int i = 0; i < m_Scene->GetPointLights().size(); i++)
		{
			
			Ray lightRay(ray.hitInfo.intersectionPoint, glm::normalize(m_Scene->GetPointLights()[i].m_Position - ray.hitInfo.intersectionPoint));
			lightRay.towardsLight = true;
			
		//	if (lightRay.hitInfo.shapeIndex == -1) {
		//		colour += CalculatePointLight(m_Scene->GetPointLights()[i], m_Materials[ray.hitInfo.shapeIndex], lightRay.Direction, ray.hitInfo, 0.5f);
		//	}
		//	else {
				for (int j = 0; j < m_Scene->GetPointLights()[i].m_SamplePositions.size(); j++) 
				{
					float r;
					if (!m_Scene->jitterON) {
						r = 0;
					}
					else
					{
						r = GeneratRandom(-m_Scene->GetPointLights()[i].halfCellsize, m_Scene->GetPointLights()[i].halfCellsize);
					}

					Ray sampleRay(ray.hitInfo.intersectionPoint, glm::normalize((m_Scene->GetPointLights()[i].m_SamplePositions[j] + r) - ray.hitInfo.intersectionPoint));
					sampleRay.towardsLight = true;
					CheckRayHits(sampleRay);
					if (sampleRay.hitInfo.shapeIndex == -1) {
						colour += CalculatePointLight(m_Scene->GetPointLights()[i], m_Materials[ray.hitInfo.shapeIndex], lightRay.Direction, ray.hitInfo, 0.5f);
					}
					else {
						if (sampleRay.hitInfo.shapeIndex == ray.hitInfo.shapeIndex) {
							colour += CalculatePointLight(m_Scene->GetPointLights()[i], m_Materials[ray.hitInfo.shapeIndex], sampleRay.Direction, ray.hitInfo, 0.5f);
						}
						else
						{
							colour += m_Scene->GetPointLights()[i].GetAmbientColour() * (m_Materials[ray.hitInfo.shapeIndex].GetAmbientColour() * 0.2f);
						}

					}
				}
				colour /= m_Scene->GetPointLights()[i].m_SamplePositions.size();
			}
		//}

		//	for (int i = 0; i < m_Scene->GetPointLights().size(); i++) {
		//		Ray lightRay(ray.hitInfo.intersectionPoint, -(m_Scene->GetPointLights()[i].GetPosition() - ray.hitInfo.intersectionPoint));
		//		lightRay.towardsLight = true;
		//		CheckRayHits(lightRay);
		//		if (lightRay.hitInfo.shapeIndex != -1) {
		//			colour += m_Scene->GetPointLights()[i].GetAmbientColour() * m_Materials[ray.hitInfo.shapeIndex].GetAmbientColour();
		//		}
		//		else
		//		{
		//			colour += CalculatePointLight(m_Scene->GetPointLights()[i], m_Materials[ray.hitInfo.shapeIndex], lightRay.Direction, ray.hitInfo, 0.5f);
		//		}
		//	}

			//colour += CalculateDirectionalLight(ray);
			//colour = glm::normalize(colour);
			//colour = CalculateDirectionalLight(ray);
		colour /= m_Scene->GetPointLights().size();

		if (rayDepth > 0 && m_Scene->reflectionsON) {
			Ray rReflect(ray.hitInfo.intersectionPoint, glm::reflect(ray.Direction, ray.hitInfo.normal));
			CheckRayHits(rReflect);

			if (rReflect.hitInfo.shapeIndex != -1) {

				Colour reflectedC = CalculateColour(rReflect, m_Materials[rReflect.hitInfo.shapeIndex].GetReflectionDepth());

				colour += reflectedC * m_Materials[rReflect.hitInfo.shapeIndex].GetSpecularColour();
			}
		}
	
	}
	else
	{
		colour = 0.2f * m_Materials[ray.hitInfo.shapeIndex].GetColour();
	}

	return colour;
}

Colour RaytraceRenderer::CalculateDirectionalLight(const Ray & ray)
{
	//Ambient
	Colour ambient = m_Scene->GetDirectionalLight().GetAmbientColour() * m_Materials[ray.hitInfo.shapeIndex].GetAmbientColour();

	//Diffuse
	Colour diffuse = m_Scene->GetDirectionalLight().GetColour() * glm::max(glm::dot(-m_Scene->GetDirectionalLight().GetDirection(), ray.hitInfo.normal), 0.0f) * m_Materials[ray.hitInfo.shapeIndex].GetColour();

	//Specular
	glm::vec3 reflectDir = glm::reflect(-m_Scene->GetDirectionalLight().GetDirection(), ray.hitInfo.normal);
	float spec = glm::pow(glm::max(glm::dot(ray.Direction, reflectDir), 0.0f), m_Materials[ray.hitInfo.shapeIndex].GetShininess());

	Colour specular = m_Scene->GetDirectionalLight().GetSpecularColour() * spec  * m_Materials[ray.hitInfo.shapeIndex].GetSpecularColour();

	return (ambient + diffuse + specular);
}

Colour RaytraceRenderer::CalculatePointLight(const PointLight & light, const Material & object, glm::vec3 & lightDir, const Hit& hitObject, const float& cutoff)
{
	lightDir = glm::normalize(lightDir);

	Colour ambient = light.GetAmbientColour() * object.GetAmbientColour();

	float diff = glm::max(glm::dot(hitObject.normal, lightDir), 0.0f);
	Colour diffuse = light.GetColour() * diff * object.GetColour();

	glm::vec3 reflectDir = glm::reflect(-lightDir, hitObject.normal);
	float spec = glm::pow(glm::max(glm::dot(lightDir, reflectDir), 0.0f), object.GetShininess());
	Colour specular = light.GetSpecularColour() * spec * object.GetSpecularColour();

	//Attenuation
	float distance = glm::length(lightDir);
	float attenuation = light.GetIntensity() / (light.Kc + light.Kl * distance + light.Kq * (distance * distance));
	attenuation = (attenuation - cutoff) * (1.0f / (1.0f - cutoff));
	attenuation = glm::max(attenuation, 0.0f);

	//ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

void RaytraceRenderer::Init()
{
	m_Width = Application::Get().GetWindow().GetWidth();
	m_Height = Application::Get().GetWindow().GetHeight();

	m_windowSurface = SDL_GetWindowSurface(Application::Get().GetWindow().m_Window);
	m_renderSurface = SDL_CreateRGBSurface(0, m_Width, m_Height, 32, 
		m_windowSurface->format->Rmask,
		m_windowSurface->format->Gmask,
		m_windowSurface->format->Bmask,
		m_windowSurface->format->Amask);
	//unsigned int * pixel = (unsigned int)m_Surface->pixels;
	//pixel[x + Y_OFFset] = 
}

float RaytraceRenderer::GeneratRandom(int  min, int  max)
{
	return (rand() % (max - min + 1)) + min;
}


