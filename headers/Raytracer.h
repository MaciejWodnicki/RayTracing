#pragma once
#include "pch.h"
#include "Mesh.h"
#include <glm/gtc/constants.hpp>

namespace Raytracer {


    inline glm::vec3 CastRay(const Ray& r, const std::vector<std::shared_ptr<Mesh>>& world) {
        using glm::vec3;

        HitPayload closestPayload;
        HitPayload payload;


        for (auto& m : world)
        {
            for (auto& t: m->_triangles)
            {
                if (t->Hit(r, payload) && payload.depth < closestPayload.depth)
                    closestPayload = payload;
            }
        }
        if (closestPayload.depth > 0 && closestPayload.depth < FLT_MAX)
            return closestPayload.color * (closestPayload.hitAngle / glm::pi<float>());
        vec3 unit_direction = r.getDirection() / glm::length(r.getDirection());
        float t = 0.5 * (unit_direction.y + 1.0);
        return (1.0f - t) * vec3(1.0f) + t * vec3(0.5, 0.7, 1.0);;
    }
}