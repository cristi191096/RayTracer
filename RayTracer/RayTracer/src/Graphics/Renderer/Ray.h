#pragma once
#include <glm\glm.hpp>


struct Hit {
	glm::vec3 intersectionPoint;
	glm::vec3 normal;
	float distanceToOrigin = 0.0f;
	int shapeIndex = -1;
	bool inShadow = false;
};

class Ray {

public:
	glm::vec3 Origin, Direction, Inv_Direction;
	int sign[3];
	bool towardsLight = false;
	Hit hitInfo; //No vector
	


	Ray(const glm::vec3& origin, const glm::vec3& direction)
		: Origin(origin), Direction(direction)
	{
		Inv_Direction = glm::vec3(1 / Direction.x, 1 / Direction.y, 1 / Direction.z);
		sign[0] = (Inv_Direction.x < 0);
		sign[1] = (Inv_Direction.y < 0);
		sign[2] = (Inv_Direction.z < 0);
	}

};