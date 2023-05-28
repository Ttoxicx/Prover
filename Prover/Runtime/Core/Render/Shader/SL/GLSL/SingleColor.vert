#version 460 core
layout (location=0) in vec3 pos;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;
void main()
{
	cameraPosition;
	gl_Position=projectionMatrix*viewMatrix*vec4(pos,1.0f);
}