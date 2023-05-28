#ifndef _POINT_H_
#define _POINT_H_

#include <vector>
#include <glm/glm.hpp>
class Point {
public:
	Point(){}
	~Point(){}
public:
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
};

#endif