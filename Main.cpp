#include "pch.h"

#include <execution>
#include <atomic>

#include "OutputFile.h"
#include "headers/Mesh.h"
#include "ObjImporter.h"
#include "Raytracer.h"



using glm::vec3;

int main()
{
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

    // Camera 
    float viewport_height = 2.0;
    float viewport_width = aspect_ratio * viewport_height;
    float focal_length = 2.0;

    vec3 origin = vec3(0, 0, 5.0f);
    vec3 horizontal = vec3(viewport_width, 0, 0);
    vec3 vertical = vec3(0, viewport_height, 0);
    vec3 lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - vec3(0, 0, focal_length);

    //light
    glm::vec3 lightDirection = glm::vec3(-1, -1, -2);
    glm::normalize(lightDirection);

    // Render
    OutputFile file(image_width, image_height);

    std::vector<int> verticalIter(image_height);
    for (int j = image_height - 1; j >= 0; --j)
        verticalIter[j] = j;

    std::atomic_int scanlinesDone = 0;
    
    std::for_each(std::execution::par, verticalIter.begin(), verticalIter.end(), [&](int j) {
        std::cerr << "\rScanlines remaining: " << image_height - scanlinesDone << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            float u = double(i) / (image_width - 1);
            float v = double(j) / (image_height - 1);
        
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            
            vec3 pixel_color = Raytracer::CastRay(r, world, lightDirection);
            
            file.ColorPixel(i,j,pixel_color);
        }
        scanlinesDone++;
    });

    file.saveFile();
	return 0;
}