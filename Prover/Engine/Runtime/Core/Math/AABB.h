#ifndef _AABB_H_
#define _AABB_H_

#include <glm/glm.hpp>
#include <limits>
#include <iostream>

class Ray;
class Plane;

class AABB
{
public:

	AABB() {
		_min = glm::vec3(std::numeric_limits<float>::max());
		_max = glm::vec3(-std::numeric_limits<float>::max());
	}

	AABB(const glm::vec3& min,const glm::vec3& max) {
		_min = min;
		_max = max;
	}

	AABB(const AABB& aabb) {
		_min = aabb._min;
		_max = aabb._max;
	}

public:

	inline const glm::vec3& min() const {
		return this->_min;
	}

	inline const glm::vec3& max() const {
		return this->_max;
	}

public:

	void setMinMax(const glm::vec3& min, const glm::vec3& max) {
		_min = min;
		_max = max;
	}

public:

	bool intersect(const AABB& aabb) const;

	bool intersect(const glm::vec3& min, const glm::vec3& max) const;

	bool intersect(const Ray& ray, glm::vec3& intersectedPoint) const;

	bool intersect(const Plane& plane) const;

public:

	friend std::ostream& operator<<(std::ostream& o,const AABB& aabb) {
		o << "AABB: \n";
		o << "min: " << aabb._min.x << ", " << aabb._min.y << ", " << aabb._min.z << "\n";
		o << "max: " << aabb._max.x << ", " << aabb._max.y << ", " << aabb._max.z << "\n";
		return o;
	}

private:
	glm::vec3 _min;
	glm::vec3 _max;
};

#endif // !_AABB_H_
