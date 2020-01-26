#include "pch.h"
#include "Camera.h"
#include "Core\Application.h"

Camera::Camera(const float& FieldOfView, const glm::vec3& position)
{
	m_Position = position;
	m_Width = Application::Get().GetWindow().GetWidth();
	m_Height = Application::Get().GetWindow().GetHeight();
	m_AspectRatio = (float)m_Width / (float)m_Height;
	m_FieldOfView = FieldOfView;


	// Default values
	//m_PanSpeed = 0.0015f;
	//m_RotationSpeed = 0.002f;
	//m_ZoomSpeed = 0.2f;


	m_Rotation = glm::vec3(90.0f, 90.0f, 0.0f);

	

	m_FocalPoint = glm::vec3(0,0,0);
	m_Distance = glm::distance(m_Position, m_FocalPoint);

	//CalculateCameraSpace();
	//CalculateRaysDirections();

	//m_Yaw = 3.0f * PI / 4.0f;
	//m_Pitch = PI / 4.0f;
}


Camera::~Camera()
{
}

void Camera::OnEvent(SDL_Event & event)
{
	

	if (event.key.keysym.sym == SDLK_UP)
	{
		Translate(glm::vec3(0, 0, 0.05));
		m_CameraIsMoving = true;
		m_CameraMoved = false;
	}
	if (event.key.keysym.sym == SDLK_DOWN)
	{
		Translate(glm::vec3(0, 0, -0.05));
		m_CameraIsMoving = true;
		m_CameraMoved = false;
	}
	if (event.key.keysym.sym == SDLK_LEFT)
	{
		Translate(glm::vec3(0.05, 0, 0));
		m_CameraIsMoving = true;
		m_CameraMoved = false;
	}
	if (event.key.keysym.sym == SDLK_RIGHT)
	{
		Translate(glm::vec3(-0.05, 0, 0));
		m_CameraIsMoving = true;
		m_CameraMoved = false;
	}

	//m_CameraIsMoving = false;
	//m_CameraMoved = true;


}
void Camera::OnEventFinished(SDL_Event & event)
{
	

	if (event.key.keysym.sym == SDLK_UP)
	{
		m_CameraMoved = true;
		//m_CameraIsMoving = false;
	}
	if (event.key.keysym.sym == SDLK_DOWN)
	{
		m_CameraMoved = true;
		//m_CameraIsMoving = false;
	}
	if (event.key.keysym.sym == SDLK_LEFT)
	{
		m_CameraMoved = true;
		//m_CameraIsMoving = false;
	}
	if (event.key.keysym.sym == SDLK_RIGHT)
	{
		m_CameraMoved = true;
		//m_CameraIsMoving = false;
	}

	//m_CameraIsMoving = false;
	//m_CameraMoved = true;


}

void Camera::CalculateRaysDirections()
{

	m_NormalisedRayDirection = m_CameraSpace - m_Position;
	m_NormalisedRayDirection = glm::normalize(m_NormalisedRayDirection);

}

void Camera::CalculateCameraSpace()
{
	for (unsigned int y = 0; y < m_Height; ++y)
	{
		for (unsigned int x = 0; x < m_Width; ++x)
		{

			double pixelNormalizedX = (x + 0.5) / m_Width;
			double pixelNormalizedY = (y + 0.5) / m_Height;

			double pixelRemappedX = (2 * pixelNormalizedX - 1)*m_AspectRatio;
			double pixelRemappedY = 1 - 2 * pixelNormalizedY;

			double pixelCameraX = pixelRemappedX * glm::tan(glm::radians(m_FieldOfView) / 2);
			double pixelCameraY = pixelRemappedY * glm::tan(glm::radians(m_FieldOfView) / 2);

			m_CameraSpace = glm::vec3(pixelCameraX, pixelCameraY, -1);
		
		}
	}
}

//Not Used yet
//glm::vec3 Camera::CalculatePosition()
//{
//	//Not Implemented
//	return glm::vec3(0, 0, 0);
//}


