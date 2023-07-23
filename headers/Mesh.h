#pragma once
#include "pch.h"
#include "Triangle.h"

class Material
{
    glm::vec4 color;
};

class Mesh {
public:
    std::vector<std::shared_ptr<Triangle>> _triangles;
    Material _material;
};