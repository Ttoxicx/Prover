#include "Math/AABB.h"
#include "Math/Plane.h"
#include "Math/Ray.h"

bool AABB::intersect(const AABB& aabb) const {
	return this->intersect(aabb._min, aabb._max);
}

bool AABB::intersect(const glm::vec3& min, const glm::vec3& max) const {
	if (this->_max.x<min.x ||
		this->_max.y<min.y ||
		this->_max.z<min.z ||
		this->_min.x>max.x ||
		this->_min.y>max.y ||
		this->_min.z>max.z)
	{
		return false;
	}
	return true;
}

//Woo
bool AABB::intersect(const Ray& ray, glm::vec3& intersectedPoint) const {
	glm::vec3 origin = ray.origin();
	glm::vec3 direction = ray.direction();
	float length = ray.length();
	float tx0 = 0.f;
	float tx1 = 0.f;
	float dx = direction.x;
	if (dx != 0) {
		float ddx = 1.f / dx;
		if (dx > 0) {
			tx0 = (_min.x - origin.x) * ddx;
			tx1 = (_max.x - origin.x) * ddx;
		}
		else {
			tx0 = (_max.x - origin.x) * ddx;
			tx1 = (_min.x - origin.x) * ddx;
		}
	}
	else {
		if (origin.x<_min.x || origin.x>_max.x) {
			return false;
		}
		else {
			tx0 = -std::numeric_limits<float>::max();
			tx1 = std::numeric_limits<float>::max();
		}
	}
	float ty0 = 0.f;
	float ty1 = 0.f;
	float dy = direction.y;
	if (dy != 0) {
		float ddy = 1.f / dy;
		if (dy > 0) {
			ty0 = (_min.y - origin.y) * ddy;
			ty1 = (_max.y - origin.y) * ddy;
		}
		else {
			ty0 = (_max.y - origin.y) * ddy;
			ty1 = (_min.y - origin.y) * ddy;
		}
	}
	else {
		if (origin.y<_min.y || origin.y>_max.y) {
			return false;
		}
		else {
			ty0 = -std::numeric_limits<float>::max();
			ty1 = std::numeric_limits<float>::max();
		}
	}
	float tz0 = 0.f;
	float tz1 = 0.f;
	float dz = direction.z;
	if (dz != 0) {
		float ddz = 1.f / dz;
		if (dz > 0) {
			tz0 = (_min.z - origin.z) * ddz;
			tz1 = (_max.z - origin.z) * ddz;
		}
		else {
			tz0 = (_max.z - origin.z) * ddz;
			tz1 = (_min.z - origin.z) * ddz;
		}
	}
	else {
		if (origin.z<_min.z || origin.z>_max.z) {
			return false;
		}
		else {
			tz0 = -std::numeric_limits<float>::max();
			tz1 = std::numeric_limits<float>::max();
		}
	}
	float t0 = std::max(tx0, std::max(ty0, tz0));
	float t1 = std::min(tx1, std::min(ty1, tz1));
	if (t1 < t0) {
		return false;
	}
	bool inside = true;
	if (origin.x<_min.x || 
		origin.y>_max.x || 
		origin.y<_min.y || 
		origin.y>_max.y || 
		origin.z<_min.z || 
		origin.z>_max.z) 
	{
		inside = false;
	}
	float t;
	if (inside) {
		t = t1;
	}
	else {
		t = t0;
	}
	glm::vec3 offset = direction * t;
	if (glm::length(offset) > length) {
		return false;
	}
	intersectedPoint = origin + offset;
	return true;
}

bool AABB::intersect(const Plane& plane) const {
	glm::vec3 min, max;
	glm::vec3 normal = plane.normal();
	if (normal.x >= 0) {
		min.x = _min.x;
		max.x = _max.x;
	}
	else {
		min.x = _max.x;
		max.x = _min.x;
	}
	if (normal.y >= 0) {
		min.y = _min.y;
		max.y = _max.y;
	}
	else {
		min.y = _max.y;
		max.y = _min.y;
	}
	if (normal.z >= 0) {
		min.z = _min.z;
		max.z = _max.z;
	}
	else {
		min.z = _max.z;
		max.z = _min.z;
	}
	int pr1 = plane.whichSide(min);
	int pr2 = plane.whichSide(max);
	if (pr1 == 0 || pr2 == 0) {
		return false;
	}
	else if (pr1 == pr2) {
		return false;
	}
	else {
		return true;
	}
}