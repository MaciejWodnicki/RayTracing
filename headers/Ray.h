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

	glm::vec3 atPosition(float t)
	{
		return _origin + t * _direction;
	}
};