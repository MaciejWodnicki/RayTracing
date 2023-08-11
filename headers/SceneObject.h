#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

class SceneObject {
public:
	virtual HitPayload Hit(const Ray& ray) const = 0;
};

