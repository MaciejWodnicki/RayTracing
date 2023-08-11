#pragma once
#include "pch.h"
#include "Triangle.h"

class Mesh {
public:
    std::vector<std::shared_ptr<SceneObject>> _primitives;
    Material _material;
};