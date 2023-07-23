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

        vector<shared_ptr<Mesh>> world;

        Assimp::Importer importer;


        const aiScene* scene = importer.ReadFile(path, aiProcess_CalcTangentSpace |
            aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices |
            aiProcess_SortByPType);

        if (nullptr == scene) {
            throw std::runtime_error("scene file not found");
        }

        //grab triangles and materials
        for (int j = 0; j < scene->mNumMeshes; j++)
        {
            std::shared_ptr<Mesh> resultMesh = std::make_shared<Mesh>();
            auto& mesh = scene->mMeshes[j];

            //material
            auto& material = scene->mMaterials[mesh->mMaterialIndex];

            aiColor4D diffuse;
            if (aiReturn_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
                resultMesh->_material._surfaceColor = glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);

            //vertices
            auto& vertices = mesh->mVertices;
            Vertex v1, v2, v3;
            for (int i = 0; i < mesh->mNumFaces; i++)
            {
                v1.position = aiVec3ToGLM(vertices[mesh->mFaces[i].mIndices[0]]);
                v2.position = aiVec3ToGLM(vertices[mesh->mFaces[i].mIndices[1]]);
                v3.position = aiVec3ToGLM(vertices[mesh->mFaces[i].mIndices[2]]);

                std::shared_ptr<Triangle> t = std::make_shared<Triangle>(v1, v2, v3);
                resultMesh->_triangles.push_back(t);
            }
            world.push_back(resultMesh);

        }
        return world;
    }
}