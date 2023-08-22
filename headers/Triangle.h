#pragma once
#include "SceneObject.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texcoord;
	glm::vec3 normal;

};

class Triangle: public SceneObject {
	
	Vertex _v1;
	Vertex _v2;
	Vertex _v3;
	glm::vec3 _faceNormal;

public:
	Triangle(Vertex v1, Vertex v2, Vertex v3, glm::vec3 color = glm::vec3(1.0f,0.0f,0.0f))
		:_v1(v1), _v2(v2), _v3(v3)
	{
		_faceNormal = glm::normalize(glm::cross(_v1.position - _v2.position, _v2.position - _v3.position));
	}

	std::string getCoordString() const {
		return "v1: " + std::to_string(_v1.position.x) + ", " + std::to_string(_v1.position.y) + ", " + std::to_string(_v1.position.z) +
			"\nv2: " + std::to_string(_v2.position.x) + ", " + std::to_string(_v2.position.y) + ", " + std::to_string(_v2.position.z) +
			"\nv3: " + std::to_string(_v3.position.x) + ", " + std::to_string(_v3.position.y) + ", " + std::to_string(_v3.position.z);
	}
	// Inherited via Hittable
	virtual HitPayload Hit(const Ray& ray) const override //-1 = back or parrarel, -2 = behind ray origin, -3 = nie jest w trojkacie
	{
		HitPayload payload;
		using namespace glm;

		//https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection.html

		vec3 v1v2 = _v2.position - _v1.position;
		vec3 v1v3 = _v3.position - _v1.position;
		vec3 pvec = cross(ray.getDirection(),v1v3);
		float det = dot(v1v2,pvec);

		if (det < 0.0005f) // promieñ jest rownolegly do plaszczyzny lub trafia w tyl plaszczyzny trojkata
		{
			payload._depth = -1.0f;
			return payload;
		}

		float invDet = 1 / det;

		vec3 tvec = ray.getOrigin() - _v1.position;
		float u = dot(tvec, pvec) * invDet;
		if (u < 0 || u > 1)
		{
			payload._depth = -2.0f;
			return payload;
		}
		vec3 qvec = cross(tvec, v1v2);
		float v = dot(ray.getDirection(), qvec) * invDet;
		if (v < 0 || u + v > 1)
		{
			payload._depth = -2.0f;
			return payload;
		}
		float t = dot(v1v3,qvec) * invDet;


		payload._depth = t;
		payload._normal = _faceNormal;


		return payload;
	}

};