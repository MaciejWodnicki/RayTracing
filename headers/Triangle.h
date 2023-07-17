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
	glm::vec3 _color;

public:
	Triangle(Vertex v1, Vertex v2, Vertex v3, glm::vec3 color = glm::vec3(1.0f,0.0f,0.0f))
		:_v1(v1), _v2(v2), _v3(v3), _color(color) 
	{
		_faceNormal = glm::normalize(glm::cross(_v1.position - _v2.position, _v2.position - _v3.position));
	}

	glm::vec3 getColor() const { return _color; }
	std::string getCoordString() const {
		return "v1: " + std::to_string(_v1.position.x) + ", " + std::to_string(_v1.position.y) + ", " + std::to_string(_v1.position.z) +
			"\nv2: " + std::to_string(_v2.position.x) + ", " + std::to_string(_v2.position.y) + ", " + std::to_string(_v2.position.z) +
			"\nv3: " + std::to_string(_v3.position.x) + ", " + std::to_string(_v3.position.y) + ", " + std::to_string(_v3.position.z);
	}
	// Inherited via Hittable
	virtual bool Hit(Ray ray, HitPayload& payload) const override
	{
		using namespace glm;

		float D = -(_faceNormal.x * _v1.position.x + _faceNormal.y * _v1.position.y + _faceNormal.z * _v1.position.z); // z rownania plaszczyzny wyliczamy D- odleglosc od origin

		float rayNormalDot =dot(_faceNormal, -ray.getDirection());

		if (glm::abs(rayNormalDot) < 0.0005f) // promieñ jest rownolegly do plaszczyzny lub trafia w tyl trojkata
		{
			return false; //idk napewno nie kolor trojkata
		}

		float t = (glm::dot(_faceNormal, ray.getOrigin()) + D) / rayNormalDot;

		if (t < 0)
			return false; // przeciecie za kamer¹

		vec3 hitPoint = ray.getOrigin() + t * ray.getDirection();

		payload.depth = t;
		payload.color = _color;
		payload.hitAngle = rayNormalDot;

		vec3 edge0 = _v2.position - _v1.position;
		vec3 edge1 = _v3.position - _v2.position;
		vec3 edge2 = _v1.position - _v3.position;
		vec3 C0 = hitPoint - _v1.position;
		vec3 C1 = hitPoint - _v2.position;
		vec3 C2 = hitPoint - _v3.position;

		float d1 = dot(_faceNormal, cross(edge0, C0));
		float d2 = dot(_faceNormal, cross(edge1, C1));
		float d3 = dot(_faceNormal, cross(edge2, C2));

		//std::cout << d1 << ", " << d2 << ", " << d3 << ", " << std::endl;
		if (d1 > 0 &&
			d2 > 0 &&
			d3 > 0)
			return true; // punkt przeciecia jest wewnatrz trojkata
		else
			return false;
	}

};