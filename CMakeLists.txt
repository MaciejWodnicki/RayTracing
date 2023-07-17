cmake_minimum_required(VERSION 3.13)
project(Raytracing)              
set(CMAKE_CXX_STANDARD 17)         

set(SOURCE_FILES main.cpp outputFile.cpp headers/Camera.h headers/ObjImporter.h headers/OutputFile.h headers/pch.h headers/Ray.h headers/Raytracer.h headers/SceneObject.h headers/Triangle.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

include_directories(${PROJECT_NAME} PUBLIC "headers")

include(C:/portable/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)


