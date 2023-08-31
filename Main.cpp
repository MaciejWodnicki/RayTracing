#include "pch.h"

#include "OutputFile.h"
#include "Mesh.h"
#include "ObjImporter.h"
#include "Raytracer.h"

#include <chrono>



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

    //timer

    auto startTime = std::chrono::high_resolution_clock::now();

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = IMAGE_WIDTH;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    //light
    glm::vec3 lightDirection = glm::normalize(glm::vec3(-1, -1, 0));// UP -Y; RIGHT -X; FORWOARD -Z;

    // Render
    OutputFile file(image_width, image_height);

    world[4].get()->_material._emission = 5.0f; // ustawienie emisyjnosci dla konkretnego elementu sceny

    Raytracer::GenerateRays(world, file, lightDirection);

    file.saveFile();

    auto endTime = std::chrono::high_resolution_clock::now();


    std::chrono::duration<float> duration = endTime - startTime;

    std::cout << std::endl << "Execution time: " << duration.count() << "s" << std::endl;

	return 0;
}