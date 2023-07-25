#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

class HitPayload {
public:
    glm::vec4 color;
    float depth = FLT_MAX;
    glm::vec3 normal;
};

class SceneObject {
public:
	virtual bool Hit(Ray ray, HitPayload& payload) const = 0;
};

