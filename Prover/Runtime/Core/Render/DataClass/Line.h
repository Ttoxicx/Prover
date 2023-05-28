#ifndef _LINE_H_
#define _LINE_H_

#include <vector>
#include <glm/glm.hpp>
class Line {
public:
	Line(){}
	~Line(){}
public:
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
};

#endif