#pragma once

#include "pch.h"
#include "Mesh.h"

#include <stdexcept>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags


namespace ObjImporter {

    glm::vec3 aiVec3ToGLM(aiVector3D vec)
    {
        glm::vec3 out;
        out.x = vec.x;
        out.y = vec.y;
        out.z = vec.z;
        return out;
    }

    std::vector<std::shared_ptr<Mesh>> ImportMeshes(std::string path)
    {
        using namespace std;

        Assimp::Importer importer;

        //import i walidacja
        const aiScene* scene = importer.ReadFile(path,
            aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices |
            aiProcess_SortByPType);

        if (scene == nullptr) {
            throw std::runtime_error("scene file not found");
        }

        //konwersja danych
        vector<shared_ptr<Mesh>> world;
        for (int j = 0; j < scene->mNumMeshes; j++)
        {
            std::shared_ptr<Mesh> resultMesh = std::make_shared<Mesh>();
            auto& mesh = scene->mMeshes[j];

            //materia³
            auto& material = scene->mMaterials[mesh->mMaterialIndex];

            aiColor4D albedo;
            float roughness;
            float metalic;
            float ior;

            if (aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &albedo)
                == aiReturn_SUCCESS)
            {
                resultMesh->_material._albedo = glm::vec4(
                    glm::max(albedo.r, 0.01f),
                    glm::max(albedo.g, 0.01f),
                    glm::max(albedo.b, 0.01f),
                    glm::max(albedo.a, 0.01f));
            }

            if (aiGetMaterialFloat(material, AI_MATKEY_ROUGHNESS_FACTOR, &roughness)
                == aiReturn_SUCCESS)
                resultMesh->_material._roughness = roughness;

            if (aiGetMaterialFloat(material, AI_MATKEY_METALLIC_FACTOR, &metalic)
                == aiReturn_SUCCESS)
                resultMesh->_material._metalic = metalic;

            if (aiGetMaterialFloat(material, AI_MATKEY_REFRACTI, &ior)
                == aiReturn_SUCCESS)
                resultMesh->_material._refractionIndex = ior;


            //wierzcho³ki
            auto& vertices = mesh->mVertices;
            Vertex v1, v2, v3;
            for (int i = 0; i < mesh->mNumFaces; i++)
            {
                v1.position = aiVec3ToGLM(vertices[mesh->mFaces[i].mIndices[0]]);
                v2.position = aiVec3ToGLM(vertices[mesh->mFaces[i].mIndices[1]]);
                v3.position = aiVec3ToGLM(vertices[mesh->mFaces[i].mIndices[2]]);

                std::shared_ptr<Triangle> t = std::make_shared<Triangle>(v1, v2, v3);
                resultMesh->_primitives.push_back(t);
            }
            world.push_back(resultMesh);
        }
        return world;
    }
}