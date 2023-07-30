#version 460 core
layout (location=0) in vec3 pos;
layout (std140,binding=0) uniform VP{
	mat4 projectionMatrix;
	mat4 viewMatrix;
};
uniform mat4 modelMatrix;
void main()
{
	gl_Position=projectionMatrix*viewMatrix*vec4(pos,1.0f);
}