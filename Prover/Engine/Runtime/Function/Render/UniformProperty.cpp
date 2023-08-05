#include "Render/UniformProperty.h"
#include "Basic/Light.h"
#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

void UniformProperties::setUp()
{
	/*GLint maxUniformBlockSize;
	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &maxUniformBlockSize);
	std::cout << "Max Uniform Block Size: " << maxUniformBlockSize << std::endl;
	std::cout << sizeof(glm::vec3) << std::endl;*/
	glGenBuffers(4, _UBOs);
	setUpCommonProperties();
	setUpDirectionalLightBuffer();
	setUpPointLightBuffer();
	setUpSpotLightBuffer();
}

//配置通用属性(视口矩阵，投影矩阵，相机位置)
void UniformProperties::setUpCommonProperties()
{
	glBindBuffer(GL_UNIFORM_BUFFER, _UBOs[0]);
	glBufferData(
		GL_UNIFORM_BUFFER,
		2 * sizeof(glm::mat4) + sizeof(glm::vec4),
		NULL, GL_DYNAMIC_DRAW
	);
	glBindBufferRange(
		GL_UNIFORM_BUFFER, 0, _UBOs[0],
		0, 2 * sizeof(glm::mat4) + sizeof(glm::vec4)
	);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

//配置静态光
void UniformProperties::setUpDirectionalLightBuffer()
{
	glBindBuffer(GL_UNIFORM_BUFFER, _UBOs[1]);
	glBufferData(
		GL_UNIFORM_BUFFER,
		MAXDIRECTIONALLIGHTCOUNT * sizeof(DirectionalLight) + sizeof(unsigned int),
		NULL, GL_DYNAMIC_DRAW
	);
	glBindBufferRange(
		GL_UNIFORM_BUFFER, 1, _UBOs[1],
		0, MAXDIRECTIONALLIGHTCOUNT * sizeof(DirectionalLight) + sizeof(unsigned int)
	);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	////Test
	//DirectionalLight Light;
	//std::cout << sizeof(Light) << std::endl;
	//std::cout << sizeof(DirectionalLight) << std::endl;
	//Light.lightColor = glm::vec4(1.f, 0.f, 1.f, 1.f);
	//Light.lightDir = glm::uvec4(-1.f, -1.f, -1.f, -1.f);
	//glBindBuffer(GL_UNIFORM_BUFFER, _UBOs[1]);
	//glBufferSubData(
	//	GL_UNIFORM_BUFFER,
	//	0, sizeof(DirectionalLight),
	//	&Light
	//);
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

//配置点光
void UniformProperties::setUpPointLightBuffer()
{
	glBindBuffer(GL_UNIFORM_BUFFER, _UBOs[2]);
	glBufferData(
		GL_UNIFORM_BUFFER,
		MAXPOINTLIGHTCOUNT * sizeof(PointLight) + sizeof(unsigned int),
		NULL, GL_DYNAMIC_DRAW
	);
	glBindBufferRange(
		GL_UNIFORM_BUFFER, 2, _UBOs[2],
		0, MAXPOINTLIGHTCOUNT * sizeof(PointLight) + sizeof(unsigned int)
	);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

//配置锥光
void UniformProperties::setUpSpotLightBuffer()
{
	glBindBuffer(GL_UNIFORM_BUFFER, _UBOs[3]);
	glBufferData(
		GL_UNIFORM_BUFFER,
		MAXSPOTLIGHTCOUNT * sizeof(SpotLight) + sizeof(unsigned int),
		NULL, GL_DYNAMIC_DRAW
	);
	glBindBufferRange(
		GL_UNIFORM_BUFFER, 3, _UBOs[3],
		0, MAXSPOTLIGHTCOUNT * sizeof(SpotLight) + sizeof(unsigned int)
	);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformProperties::clear()
{
	glDeleteBuffers(4, _UBOs);
}

//设置投影矩阵
void UniformProperties::setProjectionMatrix(const glm::mat4& projectionMatrix)
{
	glBindBuffer(GL_UNIFORM_BUFFER, _UBOs[0]);
	glBufferSubData(
		GL_UNIFORM_BUFFER,
		0, sizeof(glm::mat4),
		glm::value_ptr(projectionMatrix)
	);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

//设置视口矩阵
void UniformProperties::setViewMatrix(const glm::mat4& viewMatrix)
{
	glBindBuffer(GL_UNIFORM_BUFFER, _UBOs[0]);
	glBufferSubData(
		GL_UNIFORM_BUFFER,
		sizeof(glm::mat4), sizeof(glm::mat4),
		glm::value_ptr(viewMatrix)
	);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

//设置相机位置
void UniformProperties::setCameraPosition(const glm::vec3& cameraPos)
{
	glBindBuffer(GL_UNIFORM_BUFFER, _UBOs[0]);
	glBufferSubData(
		GL_UNIFORM_BUFFER,
		2 * sizeof(glm::mat4), sizeof(glm::vec4),
		glm::value_ptr(glm::vec4(cameraPos, 1.0f))
	);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformProperties::addDirectionalLight(std::shared_ptr<DirectionalLight> light)
{
	if (_directionalLights.size() >= MAXDIRECTIONALLIGHTCOUNT) {
		return;
	}
	_directionalLights.push_back(light);
	updateDirectionaLightBufferData();
}

void UniformProperties::addPointLight(std::shared_ptr<PointLight> light)
{
	if (_pointLights.size() >= MAXPOINTLIGHTCOUNT) {
		return;
	}
	_pointLights.push_back(light);
	updatePointLightBufferData();
}

void UniformProperties::addSpotLight(std::shared_ptr<SpotLight> light)
{
	if (_pointLights.size() >= MAXSPOTLIGHTCOUNT) {
		return;
	}
	_spotLights.push_back(light);
	updateSpotLightBufferData();
}

void UniformProperties::removeDirectionalLight(std::shared_ptr<DirectionalLight> light)
{
	auto result = _directionalLightsIndicesMap.find(light);
	if (result != _directionalLightsIndicesMap.end()) {
		_directionalLights.erase(_directionalLights.begin() + result->second);
		_directionalLightsIndicesMap.erase(result);
	}
	updateDirectionaLightBufferData();
}

void UniformProperties::removePointLight(std::shared_ptr<PointLight> light)
{
	auto result = _pointLightsIndicesMap.find(light);
	if (result != _pointLightsIndicesMap.end()) {
		_pointLights.erase(_pointLights.begin() + result->second);
		_pointLightsIndicesMap.erase(result);
	}
	updatePointLightBufferData();
}

void UniformProperties::removeSpotLight(std::shared_ptr<SpotLight> light)
{
	auto result = _spotLightsIndicesMap.find(light);
	if (result != _spotLightsIndicesMap.end()) {
		_spotLights.erase(_spotLights.begin() + result->second);
		_spotLightsIndicesMap.erase(result);
	}
	updateSpotLightBufferData();
}

void UniformProperties::clearDirectionalLight()
{
	_directionalLights.clear();
	_directionalLightsIndicesMap.clear();
	updateDirectionaLightBufferData();
}

void UniformProperties::clearPointLight()
{
	_pointLights.clear();
	_pointLightsIndicesMap.clear();
	updatePointLightBufferData();
}

void UniformProperties::clearSpotLight()
{
	_spotLights.clear();
	_spotLightsIndicesMap.clear();
	updateSpotLightBufferData();
}

void UniformProperties::updateDirectionaLightBufferData()
{
	unsigned int lightCount = _directionalLights.size();
	unsigned int lightSize = sizeof(DirectionalLight);
	_directionalLightsIndicesMap.clear();
	glBindBuffer(GL_UNIFORM_BUFFER, _UBOs[1]);
	for (unsigned int i = 0; i < lightCount; ++i) {
		glBufferSubData(
			GL_UNIFORM_BUFFER,
			i * lightSize, lightSize,
			_directionalLights.at(i).get()
		);
		_directionalLightsIndicesMap.emplace(_directionalLights.at(i), i);
	}
	glBufferSubData(
		GL_UNIFORM_BUFFER,
		MAXDIRECTIONALLIGHTCOUNT * lightSize, sizeof(unsigned int),
		&lightCount
	);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformProperties::updatePointLightBufferData()
{
	unsigned int lightCount = _pointLights.size();
	unsigned int lightSize = sizeof(PointLight);
	_pointLightsIndicesMap.clear();
	glBindBuffer(GL_UNIFORM_BUFFER, _UBOs[2]);
	for (unsigned int i = 0; i < lightCount; ++i) {
		glBufferSubData(
			GL_UNIFORM_BUFFER,
			i * lightSize, lightSize,
			_pointLights.at(i).get()
		);
		_pointLightsIndicesMap.emplace(_pointLights.at(i), i);
	}
	glBufferSubData(
		GL_UNIFORM_BUFFER,
		MAXPOINTLIGHTCOUNT * lightSize, sizeof(unsigned int),
		&lightCount
	);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformProperties::updateSpotLightBufferData()
{
	unsigned int lightCount = _spotLights.size();
	unsigned int lightSize = sizeof(SpotLight);
	_spotLightsIndicesMap.clear();
	glBindBuffer(GL_UNIFORM_BUFFER, _UBOs[3]);
	for (unsigned int i = 0; i < lightCount; ++i) {
		glBufferSubData(
			GL_UNIFORM_BUFFER,
			i * lightSize, lightSize,
			_spotLights.at(i).get()
		);
		_spotLightsIndicesMap.emplace(_spotLights.at(i), i);
	}
	glBufferSubData(
		GL_UNIFORM_BUFFER,
		MAXSPOTLIGHTCOUNT * lightSize, sizeof(unsigned int),
		&lightCount
	);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformProperties::updateSingleDirectionalLightBufferData(std::shared_ptr<DirectionalLight> light)
{
	auto result = _directionalLightsIndicesMap.find(light);
	if (result != _directionalLightsIndicesMap.end()) {
		unsigned int i = result->second;
		unsigned int lightSize = sizeof(DirectionalLight);
		glBindBuffer(GL_UNIFORM_BUFFER, _UBOs[1]);
		glBufferSubData(
			GL_UNIFORM_BUFFER,
			i * lightSize, lightSize,
			light.get()
		);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}

void UniformProperties::updateSinglePointLightBufferData(std::shared_ptr<PointLight> light)
{
	auto result = _pointLightsIndicesMap.find(light);
	if (result != _pointLightsIndicesMap.end()) {
		unsigned int i = result->second;
		unsigned int lightSize = sizeof(PointLight);
		glBindBuffer(GL_UNIFORM_BUFFER, _UBOs[2]);
		glBufferSubData(
			GL_UNIFORM_BUFFER,
			i * lightSize, lightSize,
			light.get()
		);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}

void UniformProperties::updateSingleSpotLightBufferData(std::shared_ptr<SpotLight> light)
{
	auto result = _spotLightsIndicesMap.find(light);
	if (result != _spotLightsIndicesMap.end()) {
		unsigned int i = result->second;
		unsigned int lightSize = sizeof(SpotLight);
		glBindBuffer(GL_UNIFORM_BUFFER, _UBOs[3]);
		glBufferSubData(
			GL_UNIFORM_BUFFER,
			i * lightSize, lightSize,
			light.get()
		);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}
