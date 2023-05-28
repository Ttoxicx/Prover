#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include <glm/glm.hpp>

class Mesh {
public:
	Mesh(){}
	~Mesh(){}
public:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec2> texCoords;
	std::vector<unsigned int> indices;
};

#endif // !1