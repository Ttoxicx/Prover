#include "Render/Shader/Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

Shader::Shader(const char* vscPath) {
	loadandCompileSubShader(vscPath, SHADER_TYPE::VERT);
	createShader(PROGRAM_TYPE::VERT_ONLY);
}

Shader::Shader(const char* vscPath, const char* fscPath) {
	loadandCompileSubShader(vscPath, SHADER_TYPE::VERT);
	loadandCompileSubShader(fscPath, SHADER_TYPE::FRAG);
	createShader(PROGRAM_TYPE::VERT_FRAG);
}

Shader::Shader(const char* vscPath, const char* fscPath, const char* gscPath) {
	loadandCompileSubShader(vscPath, SHADER_TYPE::VERT);
	loadandCompileSubShader(fscPath, SHADER_TYPE::FRAG);
	loadandCompileSubShader(gscPath, SHADER_TYPE::GEOM);
	createShader(PROGRAM_TYPE::VERT_GEOM_FRAG);
}

void Shader::loadandCompileSubShader(const char* path, SHADER_TYPE type)
{
	std::string shaderCode;
	std::ifstream shaderFileStream;
	shaderFileStream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	try {
		shaderFileStream.open(path);
		std::stringstream shaderstream;
		shaderstream << shaderFileStream.rdbuf();
		shaderCode = shaderstream.str();
		shaderFileStream.close();
	}
	catch (std::ifstream::failure e) {
		throw std::string(std::string(path)) + std::string(path).c_str();
	}
	const char* sc = shaderCode.c_str();
	unsigned int currentShaderId = 0;
	switch (type) {
	case SHADER_TYPE::VERT:
		_vertShaderId = glCreateShader(GL_VERTEX_SHADER);
		currentShaderId = _vertShaderId;
		break;
	case SHADER_TYPE::FRAG:
		_fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		currentShaderId = _fragShaderId;
		break;
	case SHADER_TYPE::GEOM:
		_geomShaderId = glCreateShader(GL_GEOMETRY_SHADER);
		currentShaderId = _geomShaderId;
		break;
	default:
		throw "Wrong Shader Type";
	}
	glShaderSource(currentShaderId, 1, &sc, NULL);
	glCompileShader(currentShaderId);
	glGetShaderiv(currentShaderId, GL_COMPILE_STATUS, &_buildSuccess);
	if (!_buildSuccess) {
		_errorId = currentShaderId;
	}
	return;
}

void Shader::createShader(PROGRAM_TYPE type) {
	_shaderProgramId = glCreateProgram();
	switch (type)
	{
	case PROGRAM_TYPE::VERT_ONLY:
		glAttachShader(_shaderProgramId, _vertShaderId);
		break;
	case PROGRAM_TYPE::VERT_FRAG:
		glAttachShader(_shaderProgramId, _vertShaderId);
		glAttachShader(_shaderProgramId, _fragShaderId);
		break;
	case PROGRAM_TYPE::VERT_GEOM_FRAG:
		glAttachShader(_shaderProgramId, _vertShaderId);
		glAttachShader(_shaderProgramId, _geomShaderId);
		glAttachShader(_shaderProgramId, _fragShaderId);
		break;
	default:
		throw "Wrong Program Type";
	}
	glLinkProgram(_shaderProgramId);
	glGetProgramiv(_shaderProgramId, GL_LINK_STATUS, &_buildSuccess);
	if (!_buildSuccess) {
		_errorId = _shaderProgramId;
	}
	glDeleteShader(_vertShaderId);
	glDeleteShader(_geomShaderId);
	glDeleteShader(_fragShaderId);
}

void Shader::getShaderCondition() {
	if (!_buildSuccess) {
		std::cout << "Shader: " << _shaderProgramId << "Create Failed\n" << "DETAIL:" << std::endl;
		char infolog[512];
		if (_errorId == _vertShaderId) {
			glGetShaderInfoLog(_errorId, 512, NULL, infolog);
			std::cout << "VERTEX SHADER COMPILE FAILED\n" << infolog << std::endl;
			return;
		}
		if (_errorId == _fragShaderId) {
			glGetShaderInfoLog(_errorId, 512, NULL, infolog);
			std::cout << "FRAGMENT SHADER COMPILE FAILED\n" << infolog << std::endl;
			return;
		}
		if (_errorId == _geomShaderId) {
			glGetShaderInfoLog(_errorId, 512, NULL, infolog);
			std::cout << "GEOMETRY SHADER COMPILE FAILED\n" << infolog << std::endl;
			return;
		}
		if (_errorId == _shaderProgramId) {
			glGetProgramInfoLog(_errorId, 512, NULL, infolog);
			std::cout << "PROGRAM LINK FAILED\n" << infolog << std::endl;
			return;
		}
	}
	std::cout << "Shader: " << _shaderProgramId << " Create Success" << std::endl;
}

void Shader::setParameters1b(const char* property, bool val)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform1i(loc, val);
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters2b(const char* property, const glm::bvec2& vec2)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform2iv(loc, 1, glm::value_ptr(glm::ivec2(vec2)));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters3b(const char* property, const glm::bvec3& vec3)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform3iv(loc, 1, glm::value_ptr(glm::ivec3(vec3)));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters4b(const char* property, const glm::bvec4& vec4)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform4iv(loc, 1, glm::value_ptr(glm::ivec4(vec4)));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters1i(const char* property, int val)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform1i(loc, val);
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters2i(const char* property, const glm::ivec2& vec2)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform2iv(loc, 1, glm::value_ptr(vec2));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters3i(const char* property, const glm::ivec3& vec3)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform3iv(loc, 1, glm::value_ptr(vec3));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters4i(const char* property, const glm::ivec4& vec4)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform4iv(loc, 1, glm::value_ptr(vec4));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters1ui(const char* property, unsigned int val)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform1ui(loc, val);
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters2ui(const char* property, const glm::uvec2& vec2)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform2uiv(loc, 1, glm::value_ptr(vec2));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters3ui(const char* property, const glm::uvec3& vec3)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform3uiv(loc, 1, glm::value_ptr(vec3));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters4ui(const char* property, const glm::uvec4& vec4)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform4uiv(loc, 1, glm::value_ptr(vec4));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters1f(const char* property, float val)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform1f(loc, val);
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters2f(const char* property, const glm::vec2& vec2)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform2fv(loc, 1, glm::value_ptr(vec2));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters3f(const char* property, const glm::vec3& vec3)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform3fv(loc, 1, glm::value_ptr(vec3));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters4f(const char* property, const glm::vec4& vec4)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform4fv(loc, 1, glm::value_ptr(vec4));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters1d(const char* property, double val)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform1d(loc, val);
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters2d(const char* property, const glm::dvec2& vec2)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform2dv(loc, 1, glm::value_ptr(vec2));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters3d(const char* property, const glm::dvec3& vec3)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform3dv(loc, 1, glm::value_ptr(vec3));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParameters4d(const char* property, const glm::dvec4& vec4)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniform4dv(loc, 1, glm::value_ptr(vec4));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParametersMat2f(const char* property, const glm::mat2& mat2)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(mat2));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParametersMat3f(const char* property, const glm::mat3& mat3)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(mat3));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParametersMat4f(const char* property, const glm::mat4& mat4)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat4));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParametersMat2d(const char* property, const glm::dmat2& mat2)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniformMatrix2dv(loc, 1, GL_FALSE, glm::value_ptr(mat2));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParametersMat3d(const char* property, const glm::dmat3& mat3)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniformMatrix3dv(loc, 1, GL_FALSE, glm::value_ptr(mat3));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}

void Shader::setParametersMat4d(const char* property, const glm::dmat4& mat4)
{
	int loc = glGetUniformLocation(_shaderProgramId, property);
	if (loc != -1) {
		glUniformMatrix4dv(loc, 1, GL_FALSE, glm::value_ptr(mat4));
	}
	else {
		std::cout << "Shader: " << _shaderProgramId << " Property" << " \" " << property << " \" " << "Not Found!!!\n";
	}
}