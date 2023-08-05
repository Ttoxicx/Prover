#version 460 core
layout (std140,binding=0) uniform ViewRelated{
	mat4 projectionMatrix;
	mat4 viewMatrix;
	vec3 cameraPos;
};
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNormal;
layout (location=2) in vec2 aTexCoord;
layout (location=3) in vec3 aTangent;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
out vec3 fragPos;
out vec3 normal;
out vec2 texCoord;
out vec3 tangent;
out vec3 eyePos;
void main()
{
	gl_Position=projectionMatrix*viewMatrix*modelMatrix*vec4(aPos,1.0f);
	fragPos=vec3(modelMatrix*vec4(aPos,1.0f));
	normal=normalMatrix*aNormal;
	texCoord=aTexCoord;
	tangent=vec3(modelMatrix*vec4(aTangent,0.f));
	eyePos=cameraPos;
}