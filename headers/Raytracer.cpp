#include "Raytracer.h"
#include <execution>

HitData Raytracer::TraceRay(const Ray& r, const std::vector<std::shared_ptr<Mesh>>& world)
{
    using glm::vec3;

    HitData closestPayload;
    HitData payload;

    for (auto& m : world)
    {
        for (auto& t : m->_primitives)
        {
            payload = t->Hit(r);
            if (payload._depth < closestPayload._depth && payload._depth>0.0f)
            {
                closestPayload = payload;
                closestPayload._material = m->_material;
            }
        }
    }

    //closest hit shader
    if (closestPayload._depth > 0 && closestPayload._depth < std::numeric_limits<float>::max())
    {
        return closestPayload;
    }

    //miss shader

    return Miss(r);
}

glm::vec3 Raytracer::CalculatePixel(const Ray& r, const std::vector<std::shared_ptr<Mesh>>& world, glm::vec3 lightDirection)
{
    glm::vec4 color(0.0f);
    int reflectionCount = REFLECTION_RESOLUTION;
    glm::vec4 rayColor(1.0f);

    Ray ray = r;
    for (int i = 0; i < reflectionCount; i++)
    {
        HitData payload = TraceRay(ray, world);

        if (payload._depth < 0.01f)
        {
            color += payload._material._albedo * rayColor;
            break;
        }

       //shadow
       Ray ShadowRay(ray.atPosition(payload._depth) + payload._normal * 0.0001f, -lightDirection);
       if (IsDirectlyIlluminated(ShadowRay, world, lightDirection, payload._normal))
       {
           color += payload._material._albedo *rayColor;
       }

        rayColor *= payload._material._albedo; //light accumulation

        glm::vec3 diffuse = ray.DiffuseReflectDirection(payload._normal,ray.atPosition(payload._depth), payload._material);
        glm::vec3 specular = glm::reflect(ray.getDirection(), payload._normal);

        ray.UpdateRay(ray.atPosition(payload._depth),
            glm::mix(specular, diffuse, payload._material._roughness));
    }


    color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));

    //gamma correction
    color = glm::pow(color,glm::vec4(GAMMA));

    return color;
}

void Raytracer::GenerateRays(const std::vector<std::shared_ptr<Mesh>>& world, OutputFile& file, glm::vec3 lightDirection)

{
    using glm::vec3;

    int imageHeight = file.getHeight();
    int imageWidth = file.getWidth();

    int samplesPerPixel = SAMPLES_PER_PIXEL;
    float superSamplingSpread = 0.01f;

    // Camera 
    float viewportHeight = 2.0;
    float viewportWidth = imageWidth / (float)imageHeight * viewportHeight;
    float focalLength = 2.0;

    vec3 origin = vec3(0, 0, 5.0f);
    vec3 horizontal = vec3(viewportWidth, 0, 0);
    vec3 vertical = vec3(0, viewportHeight, 0);
    vec3 bottomLeftCorner = origin - horizontal / 2.0f - vertical / 2.0f - vec3(0, 0, focalLength);


    std::vector<int> verticalIter(imageHeight);
    for (int j = imageHeight - 1; j >= 0; --j)
        verticalIter[j] = j;

    int scanlinesDone = 0;

    std::for_each(std::execution::par, verticalIter.begin(), verticalIter.end(), [&](int j) {
        std::cout << "\rScanlines remaining: " << imageHeight - scanlinesDone << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            float x = (float)i / (imageWidth - 1);
            float y = (float)j / (imageHeight - 1);

            vec3 pixelColor(0.0f);
            //supersampling
            for (int s = 0; s < samplesPerPixel; s++) 
            {
                glm::vec3 randOffset = glm::ballRand(superSamplingSpread);
                Ray ray(origin, 
                    bottomLeftCorner + x * horizontal + y * vertical - origin + randOffset);

                pixelColor += CalculatePixel(ray, world, lightDirection);
            }

            file.ColorPixel(i, j, pixelColor / (float)samplesPerPixel);
        }
        scanlinesDone++;
    });
}

bool Raytracer::IsDirectlyIlluminated(const Ray& r, const std::vector<std::shared_ptr<Mesh>>& world, glm::vec3 lightDirection, glm::vec3 surfaceNormal)
{
    using glm::vec3;

    HitData payload;

    if (glm::dot(surfaceNormal, -lightDirection) <= 0.001f)
        return false;

    for (auto& m : world)
    {
        for (auto& t : m->_primitives)
        {
            payload = t->Hit(r);
            if (payload._depth > -0.1f)
            {
                return false;
            }
        }
    }

    return true;
}

HitData Raytracer::Miss(const Ray& r)
{
    HitData payload;
    //sky color gradient
    glm::vec3 unit_direction = r.getDirection() / glm::length(r.getDirection());
    float t = 0.5 * (unit_direction.y + 1.0);
    payload._material._albedo = glm::vec4((1.0f - t) * glm::vec3(1.0f) + t * glm::vec3(0.5, 0.7, 1.0), 1.0f);
    payload._depth = -1.0f;

    return payload;
}


