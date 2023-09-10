#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <glm/glm.hpp>
#include <iostream>

class Ray;

class Triangle {
public:

	Triangle() {};

	Triangle(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2) {
		_p0 = p0;
		_p1 = p1;
		_p2 = p2;
		_normal = glm::normalize(glm::cross(p1 - p0, p2 - p1));
	}

	Triangle(const Triangle& triangle) {
		_p0 = triangle._p0;
		_p1 = triangle._p1;
		_p2 = triangle._p2;
		_normal = triangle._normal;
	}

public:

	inline const glm::vec3& normal() const {
		return _normal;
	}

	inline const glm::vec3& p0() const {
		return _p0;
	}

	inline const glm::vec3& p1() const {
		return _p1;
	}

	inline const glm::vec3& p2() const {
		return _p2;
	}

public:

	bool intersect(const Ray& ray, glm::vec3& intersectPoint) const;

public:

	friend std::ostream& operator<<(std::ostream& o, const Triangle& triangle) {
		o << "Triangle: \n";
		o << "normal: x" << triangle._normal.x << ", y" << triangle._normal.y << ", z" << triangle._normal.z << "\n";
		o << "p0: x" << triangle._p0.x << ", y" << triangle._p0.y << ", z" << triangle._p0.z << "\n";
		o << "p1: x" << triangle._p1.x << ", y" << triangle._p1.y << ", z" << triangle._p1.z << "\n";
		o << "p2: x" << triangle._p2.x << ", y" << triangle._p2.y << ", z" << triangle._p2.z << "\n";
		return o;
	}

private:
	glm::vec3 _normal;
	glm::vec3 _p0;
	glm::vec3 _p1;
	glm::vec3 _p2;
};

#endif // !_TRIANGLE_H_
