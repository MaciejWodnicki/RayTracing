#pragma once
#include "pch.h"
#include "Triangle.h"

class Material
{
public:
    glm::vec4 _surfaceColor;
    float _roughness = 1.0f;
    float _metalic = 0.0f;
    float _refractionIndex = 0.0f;
};

class Mesh {
public:
    std::vector<std::shared_ptr<SceneObject>> _primitives;
    Material _material;
};