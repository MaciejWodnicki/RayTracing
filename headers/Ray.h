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

	Ray reflect(glm::vec3 normal, glm::vec3 hitPoint, Material material)
	{
		
		glm::vec3 direction = glm::reflect(_direction, normal) + glm::linearRand(glm::vec3(-0.5f, -0.5f, 0.0f),glm::vec3(0.5f, 0.5f, 0.0f)) * material._roughness;
		glm::vec3 origin = hitPoint + normal * 0.0001f;
		
		Ray reflectedRay(origin, direction);

		return reflectedRay;
	}
};