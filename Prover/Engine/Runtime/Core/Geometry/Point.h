#ifndef _POINT_H_
#define _POINT_H_

#include "Geometry/Geometry.h"
#include <vector>
#include <glm/glm.hpp>

class Point :public Geometry {
public:
	Point() {}
	~Point() {}
public:
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
};

#endif