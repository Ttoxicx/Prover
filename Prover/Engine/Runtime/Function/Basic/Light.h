#ifndef _LIGHT_H_
#define _LIGHT_H_
#include <glm/glm.hpp>

struct Light {
	glm::vec4 lightColor;
};

struct DirectionalLight :Light {
	glm::vec4 lightDir;
};

struct PointLight :Light {
	glm::vec4 lightPos;
	float radius;
	float constant = 1.0f;
	float linear = 0.0014f;
	float quadratic = 0.000007f;
};

struct SpotLight :Light {
	glm::vec4 lightPos;
	glm::vec4 lightDir;
	float innerCos;
	float outerCos;
};

#endif // !_LIGHT_H_
