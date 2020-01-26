#pragma once

class Camera
{
public:
	bool m_CameraIsMoving = true;
	bool m_CameraMoved = true;

public:
	Camera(const float& FieldOfView = 60.0f, const glm::vec3& position = glm::vec3(0,0,0));
	~Camera();

	
	void OnEvent(SDL_Event & event);
	void OnEventFinished(SDL_Event & event);

	 glm::vec3 GetUpDirection();
	 glm::vec3 GetRightDirection();
	 glm::vec3 GetForwardDirection();				//Normalised Ray Direction
	

	inline const glm::vec3& GetPosition() const { return m_Position; }
	inline void SetPosition(const glm::vec3& position) { m_Position = position; }

	inline const glm::vec3& GetRotation() const { return m_Rotation; }
	inline void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; }

	inline const float& GetFieldOfView() const { return m_FieldOfView; }
	inline void SetFieldOfView(const float& FOV) { m_FieldOfView = FOV; }

	inline const float& GetAspectRation() const { return m_AspectRatio; }

	inline void Translate(const glm::vec3& translation) { m_Position += translation; }
	inline void Rotate(const glm::vec3& rotation) { m_Rotation += rotation; }

	inline void Translate(float x, float y, float z) { m_Position += glm::vec3(x, y, z); }
	inline void Rotate(float x, float y, float z) { m_Rotation += glm::vec3(x, y, z); }

	inline const glm::vec3& GetFocalPoint() const { return m_FocalPoint; }

	inline const glm::vec3& GetRayDirection() const { return m_NormalisedRayDirection; }

	inline bool IsCameraMoving() { return m_CameraIsMoving; }
	inline bool CameraMoved() { return m_CameraMoved; }

private:

	unsigned int m_Width, m_Height; 
	float m_AspectRatio;

	glm::vec3 m_NormalisedRayDirection;
	glm::vec3 m_CameraSpace;
	glm::vec3 m_Position, m_Rotation, m_FocalPoint;
	float m_Distance;
	float m_FieldOfView;
	float m_Yaw, m_Pitch;		//In Radians

private:
	void CalculateRaysDirections();
	void CalculateCameraSpace();

};