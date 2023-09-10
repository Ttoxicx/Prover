#include "Math/Plane.h"
#include "Math/Ray.h"
#include "Math/AABB.h"

bool Plane::intersect(const Ray& ray, glm::vec3& intersectPoint) const {
	glm::vec3 p0 = ray.origin();
	glm::vec3 p1 = getAxisAlignedPoint();
	glm::vec3 dir = ray.direction();
	if (glm::dot(dir, _normal) == 0.f) {
		return false;
	}
	float t = (glm::dot(_normal, p1) - glm::dot(_normal, p0)) / glm::dot(_normal, dir);
	glm::vec3 offset = dir * t;
	if (glm::length(offset) > ray.length()) {
		return false;
	}
	intersectPoint = p0 + offset;
	return true;
}

