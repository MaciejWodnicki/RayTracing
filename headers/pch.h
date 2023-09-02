#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

class Material
{
public:
    glm::vec4 _albedo;
    float _roughness = 1.0f;
    float _metalic = 0.0f;
    float _refractionIndex = 0.0f;
    float _emission = 0.0f;

    glm::vec4 EmitLIght()
    {
        return _albedo * _emission;
    }
};

struct HitPayload {
    Material _material;
    float _depth = std::numeric_limits<float>::max();
    glm::vec3 _normal;
};


#define SAMPLES_PER_PIXEL 1   //supersampling
#define IMAGE_WIDTH 800        //resolution
#define REFLECTION_RESOLUTION 5  //reflection depth
#define GAMMA 1/2.2f

