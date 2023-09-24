cmake_minimum_required(VERSION 3.13)
project(Raytracing)              
set(CMAKE_CXX_STANDARD 20)         

set(SOURCE_FILES main.cpp outputFile.cpp headers/ObjImporter.h headers/OutputFile.h headers/pch.h headers/Ray.h headers/Raytracer.h headers/Raytracer.cpp headers/SceneObject.h headers/Triangle.h headers/Mesh.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

include_directories(${PROJECT_NAME} PUBLIC "headers")

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)


