#include "pch.h"

#include "OutputFile.h"
#include "Mesh.h"
#include "ObjImporter.h"
#include "Raytracer.h"



using glm::vec3;

int main()
{
    //model import
    std::vector<std::shared_ptr<Mesh>> world;

    try {
        world = ObjImporter::ImportMeshes("../obj/scene.obj");
    }
    catch (std::runtime_error e) {
        std::cout << e.what();
        return -1;
    }

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 600;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    //light
    glm::vec3 lightDirection = glm::normalize(glm::vec3(-1, -1, -2));

    // Render
    OutputFile file(image_width, image_height);

    Raytracer::GenerateRays(world, file, lightDirection);

    file.saveFile();
	return 0;
}