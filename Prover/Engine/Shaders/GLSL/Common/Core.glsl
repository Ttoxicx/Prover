#version 460 core

//core defined light struct
struct DirectionalLight{
	vec3 lightColor;
	vec3 lightDir;
};
struct PointLight{
	vec3 lightColor;
	vec3 lightPos;
	float radius;
	float constant;
	float linear;
	float quadratic;
};
struct SpotLight{
	vec3 lightColor;
	vec3 lightPos;
	vec3 lightDir;
	float innerCos;
	float outerCos;
};

//camera related common buffer
layout (std140,binding=0) uniform ViewRelated{
	mat4 g_ProjectionMatrix;
	mat4 g_ViewMatrix;
	vec3 g_CameraPos;
};
//illumination related common buffer
layout (std140,binding=1) uniform DirectionalLights{
	
	DirectionalLight g_DirectionalLight[1000];
	uint g_DirectionalLightCount;
};
layout (std140,binding=2) uniform PointLights{
	
	PointLight g_PointLight[100];
	uint g_PointLightCount;
};
layout (std140,binding=3) uniform SpotLights{
	
	SpotLight g_SpotLight[100];
	uint g_SpotLightCount;
};
