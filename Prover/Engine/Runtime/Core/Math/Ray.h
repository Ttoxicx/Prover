#ifndef _RAY_H_
#define _RAY_H_

#include<glm/glm.hpp>
#include<iostream>
#include<limits>

#include "Math/AABB.h"
#include "Math/Plane.h"
#include "Math/Triangle.h"
#include "Math/LineSegment.h"

class Ray {
public:

	Ray() {
		_origin = glm::vec3(0.f);
		_direction = glm::vec3(0.f, 0.f, -1.f);
		_length = std::numeric_limits<float>::max();
	}

	Ray(const glm::vec3& origin, const glm::vec3& direction, float length = 1e+4f) {
		_origin = origin;
		_direction = direction;
		_length = length;
	}

	Ray(const Ray& ray) {
		_origin = ray._origin;
		_direction = ray._direction;
		_length = ray._length;
	}

public:

	inline const glm::vec3& origin() const {
		return _origin;
	}

	inline const glm::vec3& direction() const {
		return _direction;
	}

	inline float length() const {
		return _length;
	}

public:

	void setOriginAndDirection(const glm::vec3& origin, const glm::vec3& direction) {
		_origin = origin;
		_direction = direction;
	}

	void setLength(float length) {
		_length = length;
	}

public:
	
	bool intersect(const AABB& aabb, glm::vec3& intersectPoint) const {
		return aabb.intersect(*this, intersectPoint);
	}

	bool intersect(const Plane& plane, glm::vec3& intersectPoint) const {
		return plane.intersect(*this, intersectPoint);
	}

	bool intersect(const Triangle& triangle, glm::vec3& intersectPoint) const {
		return triangle.intersect(*this, intersectPoint);
	}

	bool intersect(const LineSegment& lineSegment, glm::vec3& intersectPoint, float tolerance = 1e-5f) const {
		return lineSegment.intersect(*this, intersectPoint, tolerance);
	}

	bool intersect(const Ray& ray, glm::vec3& intersectPoint, float tolerance = 1e-5f) {
		glm::vec3 crossProduct = glm::cross(_direction, ray._direction);
		if (glm::length(crossProduct)) {
			return false;
		}
		float dcross = 1.f / glm::dot(crossProduct, crossProduct);
		float t1 = glm::dot(glm::cross(ray._origin - _origin, ray._direction), crossProduct);
		float t2 = glm::dot(glm::cross(ray._origin - _origin, _direction), crossProduct);
		if (t1 < 0.f || t2 < 0.f) {
			return false;
		}
		glm::vec3 offset1 = _direction * t1;
		glm::vec3 offset2 = ray._direction * t2;
		if (glm::length(offset1) > _length || glm::length(offset2) > ray._length) {
			return false;
		}
		glm::vec3 intersect1 = _origin + offset1;
		glm::vec3 intersect2 = ray._origin + offset2;
		if (glm::length(intersect1 - intersect2) > tolerance) {
			return false;
		}
		intersectPoint = intersect2;
		return true;
	}

public:

	friend std::ostream& operator<<(std::ostream& o, const Ray& ray) {
		o << "Ray: \n";
		o << "origin: " << ray._origin.x << ", " << ray._origin.y << ", " << ray._origin.z << "\n";
		o << "direction: " << ray._direction.x << ", " << ray._direction.y << ", " << ray._direction.z << "\n";
		o << "length: " << ray._length << "\n";
		return o;
	}

private:
	glm::vec3 _origin;
	glm::vec3 _direction;
	float _length;
};

#endif // !_RAY_H_
