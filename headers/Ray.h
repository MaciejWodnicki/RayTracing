#pragma once

#include "pch.h"

class Ray {


	glm::vec3 m_origin;
	glm::vec3 m_direction;

public:
	Ray() {}
	Ray(const glm::vec3& origin, const glm::vec3& direction) : m_origin(origin), m_direction(direction) {}

	glm::vec3 getOrigin() const { return m_origin; }
	glm::vec3 getDirection() const { return m_direction; }

	glm::vec3 atPosition(float t)
	{
		return m_origin + t * m_direction;
	}
};