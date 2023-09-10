#include "Math/LineSegment.h"
#include "Math/Ray.h"

//相似三角形法 https://blog.csdn.net/xdedzl/article/details/86009147
bool LineSegment::intersect(const Ray& ray, glm::vec3& intersectPoint, float tolerance) const {
	glm::vec3 rayOrigin = ray.origin();
	glm::vec3 rayDir = ray.direction() * ray.length();
	glm::vec3 segmentOrigin = _p0;
	glm::vec3 segmentDir = _p1 - _p0;
	if (glm::dot(ray.direction(), _direction) == 1.f) {
		return false;
	}
	glm::vec3 startPointSeg = segmentOrigin - rayOrigin;
	glm::vec3 vecS1 = glm::cross(rayDir, segmentDir);
	glm::vec3 vecs2 = glm::cross(startPointSeg, segmentDir);
	float num = glm::dot(startPointSeg, vecS1);
	if (num > tolerance || num < -tolerance) {
		return false;
	}
	float num2 = glm::dot(vecs2, vecS1) / glm::length(vecS1);
	if (num2 >= 1.f || num2 < 0.f) {
		return false;
	}
	intersectPoint = rayOrigin + rayDir * num2;
	return true;
}