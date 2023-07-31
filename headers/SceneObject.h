#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

struct HitPayload {
    glm::vec4 color;
    float depth = FLT_MAX;
    glm::vec3 normal;
};

class SceneObject {
public:
	virtual HitPayload Hit(const Ray& ray) const = 0;
};

