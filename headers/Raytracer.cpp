#include "Raytracer.h"
#include <execution>

glm::vec3 Raytracer::CastRay(const Ray& r, const std::vector<std::shared_ptr<Mesh>>& world, glm::vec3 lightDirection)
{
    using glm::vec3;

    HitPayload closestPayload;
    HitPayload payload;

    for (auto& m : world)
    {
        for (auto& t : m->_primitives)
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
        float lightAngleFactor = glm::max<float>(glm::dot(closestPayload.normal, -lightDirection), 0.0f) / glm::pi<float>();
        return closestPayload.color * lightAngleFactor;
    }
    vec3 unit_direction = r.getDirection() / glm::length(r.getDirection());
    float t = 0.5 * (unit_direction.y + 1.0);
    return (1.0f - t) * vec3(1.0f) + t * vec3(0.5, 0.7, 1.0);;
}

void Raytracer::GenerateRays(const std::vector<std::shared_ptr<Mesh>>& world, OutputFile& file, glm::vec3 lightDirection)

{
    using glm::vec3;

    int image_height = file.getHeight();
    int image_width = file.getWidth();

    // Camera 
    float viewport_height = 2.0;
    float viewport_width = image_width / (float)image_height * viewport_height;
    float focal_length = 2.0;

    vec3 origin = vec3(0, 0, 5.0f);
    vec3 horizontal = vec3(viewport_width, 0, 0);
    vec3 vertical = vec3(0, viewport_height, 0);
    vec3 lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - vec3(0, 0, focal_length);


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

            vec3 pixel_color = CastRay(r, world, lightDirection);

            file.ColorPixel(i, j, pixel_color);
        }
        scanlinesDone++;
        });
}

glm::vec3 Raytracer::Miss(const Ray& r)
{
    return glm::vec3(-1.0f);
}
