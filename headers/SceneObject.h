#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

class HitPayload {
public:
    glm::vec3 color;
    float depth = FLT_MAX;
    float hitAngle = 0.0f;
};

class SceneObject {
public:
	virtual bool Hit(Ray ray, HitPayload& payload) const = 0;
};

