#pragma once
#include "pch.h"
#include "Mesh.h"
#include <glm/gtc/constants.hpp>

namespace Raytracer {


    glm::vec3 CastRay(const Ray& r, const std::vector<std::shared_ptr<Mesh>>& world, glm::vec3  lightDirection) {
        using glm::vec3;

        HitPayload closestPayload;
        HitPayload payload;

        for (auto& m : world)
        {
            for (auto& t: m->_triangles)
            {
                payload = t->Hit(r);
                if (payload.depth < closestPayload.depth && payload.depth>0.0f)
                {
                    closestPayload = payload;
                    closestPayload.color = m->_material._surfaceColor;
                }
            }
        }
        if (closestPayload.depth > 0 && closestPayload.depth < std::numeric_limits<float>::max())
        {
            float lightAngleFactor = glm::max<float>(glm::dot(closestPayload.normal,-lightDirection),0.0f)/glm::pi<float>();
            return closestPayload.color * lightAngleFactor;
        }
        vec3 unit_direction = r.getDirection() / glm::length(r.getDirection());
        float t = 0.5 * (unit_direction.y + 1.0);
        return (1.0f - t) * vec3(1.0f) + t * vec3(0.5, 0.7, 1.0);;
    }



    glm::vec3 Miss(const Ray& r)
    {
        return glm::vec3(-1.0f);
    }



}