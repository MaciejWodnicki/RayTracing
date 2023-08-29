#pragma once

#include "pch.h"

class Ray {


	glm::vec3 _origin;
	glm::vec3 _direction;

public:
	Ray() {}
	Ray(const glm::vec3& origin, const glm::vec3& direction) : _origin(origin), _direction(direction) {}

	glm::vec3 getOrigin() const { return _origin; }
	glm::vec3 getDirection() const { return _direction; }

	glm::vec3 atPosition(float t) const 
	{
		return _origin + t * _direction;
	}

	glm::vec3 DiffuseReflectDirection(glm::vec3 normal, glm::vec3 hitPoint, Material material)
	{
		
		glm::vec3 randomDirection = glm::sphericalRand(1.0f);

		if (glm::dot(randomDirection, normal) < 0.001f)
			randomDirection = -randomDirection;

		randomDirection = glm::normalize(normal + randomDirection);

		return randomDirection;
	}

	Ray& UpdateRay(glm::vec3 origin, glm::vec3 direction)
	{
		_origin = origin;
		_direction = direction;
		return *this;
	}
};