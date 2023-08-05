#version 460 core
struct DirectionalLight{
	vec3 lightColor;
	vec3 lightDir;
};
struct PointLight{
	vec3 lightColor;
	vec3 lightPosition;
	float radius;
	float constant;
	float linear;
	float quadratic;
};
struct SpotLight{
	vec3 lightPos;
	vec3 lightDir;
	vec3 lightColor;
	float innerCos;
	float outerCos;
};
layout (std140,binding=1) uniform DirectionalLights{
	
	DirectionalLight directionalLight[1000];
	uint staticLightCount;
};
layout (std140,binding=2) uniform PointLights{
	
	PointLight pointLight[100];
	uint pointLightCount;
};
layout (std140,binding=3) uniform SpotLights{
	
	SpotLight spotLight[100];
	uint spotLightCount;
};
uniform vec4 color;
void main()
{
	color;
	gl_FragColor=vec4(directionalLight[0].lightColor,1.f);
}