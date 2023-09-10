#ifndef _LINESEGMENT_H_
#define _LINESEGMENT_H_

#include <glm/glm.hpp>
#include <iostream>

class Ray;

class LineSegment {
public:

	LineSegment() {};

	LineSegment(const glm::vec3& p0, const glm::vec3& p1) {
		_p0 = p0;
		_p1 = p0;
		_direction = glm::normalize(p1 - p0);
		_length = glm::length(p1 - p0);
	}

	LineSegment(const LineSegment& lineSegment) {
		_p0 = lineSegment._p0;
		_p1 = lineSegment._p1;
		_direction = lineSegment._direction;
		_length = lineSegment._length;
	}

public:

	inline const glm::vec3& p0() const {
		return _p0;
	}

	inline const glm::vec3& p1() const {
		return _p1;
	}

	inline const glm::vec3& normal() const {
		return _direction;
	}

	inline float length() const {
		return _length;
	}

public:

	bool intersect(const Ray& ray, glm::vec3& intersectPoint, float tolerance = 1e-5f) const;

public:

	friend std::ostream& operator<<(std::ostream& o, const LineSegment& lineSegment) {
		o << "LineSegment: \n";
		o << "normal: x" << lineSegment._direction.x << ", y" << lineSegment._direction.y << ", z" << lineSegment._direction.z << "\n";
		o << "length: " << lineSegment._length << "\n";
		o << "p0: x" << lineSegment._p0.x << ", y" << lineSegment._p0.y << ", z" << lineSegment._p0.z << "\n";
		o << "p1: x" << lineSegment._p1.x << ", y" << lineSegment._p1.y << ", z" << lineSegment._p1.z << "\n";
		return o;
	}

private:
	glm::vec3 _p0;
	glm::vec3 _p1;
	glm::vec3 _direction;
	float _length;
};

#endif // !_LINESEGMENT_H_
