#pragma once
#include "pch.h"
#include "Mesh.h"
#include "OutputFile.h"
#include <glm/gtc/constants.hpp>

namespace Raytracer {

    void GenerateRays(const std::vector<std::shared_ptr<Mesh>>& world, OutputFile& file, glm::vec3 lightDirection);

    glm::vec3 CastRay(const Ray& r, const std::vector<std::shared_ptr<Mesh>>& world, glm::vec3  lightDirection);

    glm::vec3 Miss(const Ray& r);

}