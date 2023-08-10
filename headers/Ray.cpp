#include "Ray.h"

Ray Ray::reflect(glm::vec3 normal, glm::vec3 newOrigin)
{
    _direction = glm::reflect(_direction, normal);
    _origin = newOrigin + normal * 0.001f;
    return *this;
}
