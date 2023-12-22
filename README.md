# RayTracing
C++ project which renders an image utilizing the raytracing method.

# How to
The project uses two libraries: glm and ASSIMP.
It is recommended to use vcpkg for dependency management, as cMake will link them for you.

Build with cmake into the build directory.

The program was tested on .obj files exported from blender 3.5 with "Pbr extension" and triangulation enabled.
In case the scene files are not recognized you may need to manually remove "aniso" and "anisor" parameters from the .mtl file

Image resolution, number of samples per pixel, depth of reflections as well as Gamma value can be adjusted in pch.h file.

![image](https://github.com/MaciejWodnicki/RayTracing/assets/101054402/1ac8d11b-0a54-4c56-a948-dc6eae232792)
