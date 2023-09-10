#include "Math/Triangle.h"
#include "Math/Ray.h"

//Moller-Trumbore https://blog.csdn.net/zhanxi1992/article/details/109903792
bool Triangle::intersect(const Ray& ray, glm::vec3& intersectPoint) const {
	glm::vec3 E1 = _p1 - _p0;
	glm::vec3 E2 = _p2 - _p0;
	glm::vec3 S = ray.origin() - _p0;
	glm::vec3 S1 = glm::cross(ray.direction(), E2);
	glm::vec3 S2 = glm::cross(S, E1);
	float coeff = 1.f / glm::dot(S1, E1);
	float t = glm::dot(S2, E2) * coeff;
	float u = glm::dot(S1, S) * coeff;
	float v = glm::dot(S2, ray.direction()) * coeff;
	if (t >= 0.f && u >= 0.f && v >= 0.f && (1.f - u - v) >= 0.f) {
		glm::vec3 offset = ray.direction() * t;
		if (glm::length(offset) > ray.length()) {
			return false;
		}
		else {
			intersectPoint = ray.origin() + offset;
			return true;
		}
	}
	return false;
}