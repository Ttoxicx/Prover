#ifndef _PLANE_H_
#define _PLANE_H_

#include <glm/glm.hpp>
#include <iostream>

class Ray;

class Plane {
public:

	Plane() {
		_normal = glm::vec3(0, 0, 1.f);
		_a = 0;
		_b = 0;
		_c = 1.f;
		_d = 0.f;
	}

	Plane(const glm::vec3& normal, const glm::vec3& point) {
		_normal = normal;
		_a = normal.x;
		_b = normal.y;
		_c = normal.z;
		_d = -(_a * point.x + _b * point.y + _c * point.z);
	}

	Plane(const glm::vec3& normal, float d) {
		_normal = normal;
		_a = normal.x;
		_b = normal.y;
		_c = normal.z;
		_d = d;
	}

	Plane(float a, float b, float c, float d) {
		_normal = glm::normalize(glm::vec3(a, b, c));
		_a = a;
		_b = b;
		_c = c;
		_d = d;
	}

public:

	inline const glm::vec3& normal() const {
		return _normal;
	}

public:

	const glm::vec3& projectionPoint(const glm::vec3& point) const {
		glm::vec3 planePoint = getAxisAlignedPoint();
		glm::vec3 offset = point - planePoint;
		float dot = glm::dot(_normal, glm::normalize(offset));
		glm::vec3 offsetAlongNormal = _normal * dot * glm::length(offset);
		return point - offsetAlongNormal;
	}

	const glm::vec3 getAxisAlignedPoint() const {
		if (_d == 0.f) {
			return glm::vec3(0.f);
		}
		if (_a != 0.f) {
			return glm::vec3(-_d / _a, 0.f, 0.f);
		}
		if (_b != 0.f) {
			return glm::vec3(0.f, -_d / _b, 0.f);
		}
		if (_c != 0.f) {
			return glm::vec3(0.f, 0.f, -_d / _c);
		}
		throw "Plane is Not Valid";
	}

	int whichSide(const glm::vec3& point) const {
		glm::vec3 planePoint = getAxisAlignedPoint();
		glm::vec3 offset = point - planePoint;
		float dot = glm::dot(_normal, glm::normalize(offset));
		if (dot > 0.f) {
			return 1;
		}
		else if (dot == 0.f) {
			return 0;
		}
		else {
			return -1;
		}
	}

	bool intersect(const Ray& ray, glm::vec3& intersectPoint) const;
	
public:

	friend std::ostream& operator<<(std::ostream& o, const Plane& plane) {
		o << "Plane: \n";
		o << "normal: " << plane._normal.x << ", " << plane._normal.y << ", " << plane._normal.z << "\n";
		o << "parameter: a " << plane._a << ", b " << plane._b << ", c " << plane._c << ", d " << plane._d << "\n";
		return o;
	}

private:
	glm::vec3 _normal;
	float _a;
	float _b;
	float _c;
	float _d;
};

#endif // !_PLANE_H_
