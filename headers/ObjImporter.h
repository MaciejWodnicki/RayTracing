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

        std::vector<glm::vec4> colors = std::vector<glm::vec4>();

            for (unsigned int i = 0; i < scene->mNumMeshes; i++)
            {
                const aiMesh* model = scene->mMeshes[i];
                const aiMaterial* mtl = scene->mMaterials[model->mMaterialIndex];

                glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                aiColor4D diffuse;
                if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
                    color = glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
                colors.push_back(color);

            }

        for (int j = 0; j < scene->mNumMeshes; j++)
        {
            std::shared_ptr<Mesh> resultMesh = std::make_shared<Mesh>();
            auto mesh = scene->mMeshes[j];
            auto vertices = mesh->mVertices;
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