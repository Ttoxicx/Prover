#include "Render/Interface/OpenGL/Renderer.h"
#include "Render/Geometry/Mesh.h"
#include "Render/Geometry/Line.h"
#include "Render/Geometry/Point.h"
#include "Render/Interface/OpenGL/Shader.h"
#include "Render/Camera/Camera.h"
#include "Render/Light/Light.h"
#include "Render/Interface/OpenGL/UniformProperty.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

GLRenderer::GLRenderer()
{
	_mainCamera = std::make_shared<Camera>();
	_uniformProperties = std::make_shared<GLUniformProperties>();
	_uniformProperties->setUp();
}

GLRenderer::~GLRenderer()
{
	_uniformProperties->clear();
}

std::shared_ptr<GLRenderer> GLRenderer::getInstance()
{
	if (_glRenderer == nullptr) {
		_glRenderer = std::make_shared<GLRenderer>();
	}
	return _glRenderer;
}

std::shared_ptr<GLGeometryRenderBuffer> GLRenderer::setUpMeshGeometryRenderBuffer(Mesh* mesh)
{
	std::shared_ptr<GLGeometryRenderBuffer> buffer(new GLGeometryRenderBuffer);
	buffer->VAO = std::make_shared<unsigned int>();
	buffer->VBO = std::make_shared<unsigned int>();
	buffer->EBO = std::make_shared<unsigned int>();
	glGenVertexArrays(1, buffer->VAO.get());
	glGenBuffers(1, buffer->VBO.get());
	glGenBuffers(1, buffer->EBO.get());
	glBindVertexArray(*buffer->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *buffer->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *buffer->EBO);
	unsigned int sizeofPoints = mesh->vertices.size() * sizeof(glm::vec3);
	unsigned int sizeofNormals = mesh->normals.size() * sizeof(glm::vec3);
	unsigned int sizeofTex = mesh->texCoords.size() * sizeof(glm::vec2);
	unsigned int sizeofTangents = mesh->tangents.size() * sizeof(glm::vec3);
	unsigned int sizeofIndices = mesh->indices.size()*sizeof(unsigned int);
	unsigned int pointOffset = 0;
	unsigned int normalOffset = sizeofPoints;
	unsigned int texOffset = sizeofPoints + sizeofNormals;
	unsigned int tangentOffset = sizeofPoints + sizeofNormals + sizeofTangents;
	glBufferData(GL_ARRAY_BUFFER, sizeofPoints + sizeofNormals + sizeofTex + sizeofTangents, NULL, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofIndices, NULL, GL_STATIC_DRAW);
	if (!mesh->vertices.empty()) {
		glBufferSubData(GL_ARRAY_BUFFER, pointOffset, sizeofPoints, &(mesh->vertices[0]));
	}
	if (!mesh->normals.empty()) {
		glBufferSubData(GL_ARRAY_BUFFER, normalOffset, sizeofNormals, &(mesh->normals[0]));
	}
	if (!mesh->texCoords.empty()) {
		glBufferSubData(GL_ARRAY_BUFFER, texOffset, sizeofTex, &(mesh->texCoords[0]));
	}
	if (!mesh->tangents.empty()) {
		glBufferSubData(GL_ARRAY_BUFFER, tangentOffset, sizeofTangents, &(mesh->tangents[0]));
	}
	if (!mesh->indices.empty()) {
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeofIndices, &(mesh->indices[0]));
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)pointOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)normalOffset);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)texOffset);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)tangentOffset);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glBindVertexArray(0);
	return buffer;
}
std::shared_ptr<GLGeometryRenderBuffer> GLRenderer::setUpLineGeometryRenderBuffer(Line* line)
{
	std::shared_ptr<GLGeometryRenderBuffer> buffer(new GLGeometryRenderBuffer);
	buffer->VAO = std::make_shared<unsigned int>();
	buffer->VBO = std::make_shared<unsigned int>();
	buffer->EBO = std::make_shared<unsigned int>();
	glGenVertexArrays(1, buffer->VAO.get());
	glGenBuffers(1, buffer->VBO.get());
	glGenBuffers(1, buffer->EBO.get());
	glBindVertexArray(*buffer->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *buffer->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *buffer->EBO);
	unsigned int sizeofPoints = line->vertices.size() * sizeof(glm::vec3);
	unsigned int sizeofIndices = line->indices.size() * sizeof(unsigned int);
	unsigned int pointOffset = 0;
	glBufferData(GL_ARRAY_BUFFER, sizeofPoints, NULL, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofIndices, NULL, GL_STATIC_DRAW);
	if (!line->vertices.empty()) {
		glBufferSubData(GL_ARRAY_BUFFER, pointOffset, sizeofPoints, &(line->vertices[0]));
	}
	if (!line->indices.empty()) {
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeofIndices, &(line->indices[0]));
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)pointOffset);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	return buffer;
}
std::shared_ptr<GLGeometryRenderBuffer> GLRenderer::setUpPointGeometryRenderBuffer(Point* point)
{
	std::shared_ptr<GLGeometryRenderBuffer> buffer(new GLGeometryRenderBuffer);
	buffer->VAO = std::make_shared<unsigned int>();
	buffer->VBO = std::make_shared<unsigned int>();
	buffer->EBO = std::make_shared<unsigned int>();
	glGenVertexArrays(1, buffer->VAO.get());
	glGenBuffers(1, buffer->VBO.get());
	glGenBuffers(1, buffer->EBO.get());
	glBindVertexArray(*buffer->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *buffer->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *buffer->EBO);
	unsigned int sizeofPoints = point->vertices.size() * sizeof(glm::vec3);
	for (int i = 0; i < point->vertices.size(); ++i) {
		point->indices.push_back(i);
	}
	unsigned int pointOffset = 0;
	glBufferData(GL_ARRAY_BUFFER, sizeofPoints, NULL, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, point->indices.size() * sizeof(unsigned int), NULL, GL_STATIC_DRAW);
	if (!point->vertices.empty()) {
		glBufferSubData(GL_ARRAY_BUFFER, pointOffset, sizeofPoints, &(point->vertices[0]));
	}
	if (!point->indices.empty()) {
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeofPoints, &(point->indices[0]));
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)pointOffset);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	return buffer;
}
void GLRenderer::deleteGeometryRenderBuffer(GLGeometryRenderBuffer* buffer)
{
	glDeleteBuffers(1, buffer->VBO.get());
	glDeleteBuffers(1, buffer->EBO.get());
	glDeleteVertexArrays(1, buffer->VAO.get());
}

void GLRenderer::drawMesh(std::shared_ptr<GLMeshRenderUnit> mru)
{
	auto rendersetting = mru->renderSet;
	if (rendersetting.getFaceCullMode() == GLRenderSetting::FaceCullMode::CullFront) {
		glCullFace(GL_FRONT);
	}
	if (rendersetting.getFaceCullMode() == GLRenderSetting::FaceCullMode::CullBack) {
		glCullFace(GL_BACK);
	}
	if (rendersetting.getFaceCullMode() == GLRenderSetting::FaceCullMode::Off) {
		glDisable(GL_CULL_FACE);
	}
	if (rendersetting.getWireFrameMode() == GLRenderSetting::WireFrameMode::On) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	auto buffer = _meshRenderMapping.at(mru);
	glUseProgram(mru->shader->getShaderId());
	glBindVertexArray(*(buffer->VAO));
	glDrawElements(GL_TRIANGLES, mru->mesh->indices.size(), GL_UNSIGNED_INT, (void*)0);
	updateShaderCommonAttribute();
	glBindVertexArray(0);
	glUseProgram(0);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GLRenderer::drawLine(std::shared_ptr<GLLineRenderUnit> lru)
{
	auto buffer = _lineRenderMapping.at(lru);
	glBindVertexArray(*(buffer->VAO));
	glUseProgram(lru->shader->getShaderId());
	updateShaderCommonAttribute();
	glBindVertexArray(0);
	glUseProgram(0);
	glDrawElements(GL_LINE, lru->line->indices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

void GLRenderer::drawPoint(std::shared_ptr<GLPointRenderUnit> pru)
{
	auto buffer = _pointRenderMapping.at(pru);
	glBindVertexArray(*(buffer->VAO));
	glUseProgram(pru->shader->getShaderId());
	updateShaderCommonAttribute();
	glBindVertexArray(0);
	glUseProgram(0);
	glDrawElements(GL_POINT, pru->point->indices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

void GLRenderer::setViewMatrix()
{
	if (_mainCamera != nullptr) {
		_uniformProperties->setViewMatrix(_mainCamera->getViewMatrix());
	}
	else {
		_uniformProperties->setViewMatrix(glm::mat4(1));
	}
}
void GLRenderer::setProjectionMatrix()
{
	if (_mainCamera != nullptr) {
		_uniformProperties->setProjectionMatrix(_mainCamera->getProjcetionMatrix());
	}
	else {
		_uniformProperties->setProjectionMatrix(glm::mat4(1));
	}
}

void GLRenderer::setCameraPosition() {
	if (_mainCamera != nullptr) {
		_uniformProperties->setCameraPosition(_mainCamera->getCameraLocation());
	}
	else {
		_uniformProperties->setCameraPosition(glm::vec3(0.f));
	}
}

void GLRenderer::updateShaderCommonAttribute()
{
	setProjectionMatrix();
	setViewMatrix();
	setCameraPosition();
}

void GLRenderer::prepairToRender()
{
	for (auto value : _meshRenderUnitsRemove) {
		auto buffer = _meshRenderMapping.at(value);
		deleteGeometryRenderBuffer(buffer.get());
		_meshRenderMapping.erase(value);
	}
	for (auto value : _lineRenderUnitsRemove) {
		auto buffer = _lineRenderMapping.at(value);
		deleteGeometryRenderBuffer(buffer.get());
		_lineRenderMapping.erase(value);
	}
	for (auto value : _pointRenderUnitsRemove) {
		auto buffer = _pointRenderMapping.at(value);
		deleteGeometryRenderBuffer(buffer.get());
		_pointRenderMapping.erase(value);
	}
	for (auto value : _meshRenderUnitsAdd) {
		auto val = _meshRenderMapping.find(value);
		if (val == _meshRenderMapping.end()) {
			auto buffer = setUpMeshGeometryRenderBuffer(value->mesh.get());
			_meshRenderMapping.emplace(value, buffer);
		}
	}
	for (auto value : _lineRenderUnitsAdd) {
		auto val = _lineRenderMapping.find(value);
		if (val == _lineRenderMapping.end()) {
			auto buffer = setUpLineGeometryRenderBuffer(value->line.get());
			_lineRenderMapping.emplace(value, buffer);
		}
	}
	for (auto value : _pointRenderUnitsAdd) {
		auto val = _pointRenderMapping.find(value);
		if (val == _pointRenderMapping.end()) {
			auto buffer = setUpPointGeometryRenderBuffer(value->point.get());
			_pointRenderMapping.emplace(value, buffer);
		}
	}
	_meshRenderUnitsRemove.clear();
	_lineRenderUnitsRemove.clear();
	_pointRenderUnitsRemove.clear();
	_meshRenderUnitsAdd.clear();
	_lineRenderUnitsAdd.clear();
	_pointRenderUnitsAdd.clear();
}

void GLRenderer::addDirectionalLight(std::shared_ptr<DirectionalLight> light)
{
	_uniformProperties->addDirectionalLight(light);
}

void GLRenderer::addPointLight(std::shared_ptr<PointLight> light)
{
	_uniformProperties->addPointLight(light);
}

void GLRenderer::addSpotLight(std::shared_ptr<SpotLight> light)
{
	_uniformProperties->addSpotLight(light);
}

void GLRenderer::removeDirectionalLight(std::shared_ptr<DirectionalLight> light)
{
	_uniformProperties->removeDirectionalLight(light);
}

void GLRenderer::removePointLight(std::shared_ptr<PointLight> light)
{
	_uniformProperties->removePointLight(light);
}

void GLRenderer::removeSpotLight(std::shared_ptr<SpotLight> light)
{
	_uniformProperties->removeSpotLight(light);
}

void GLRenderer::render()
{
	if (_mainCamera) {
		_mainCamera->updateCameraInfo();
	}
	
	for (auto value : _meshRenderMapping) {
		drawMesh(value.first);
	}
	for (auto value : _lineRenderMapping) {
		drawLine(value.first);
	}
	for (auto value : _pointRenderMapping) {
		drawPoint(value.first);
	}
}
void GLRenderer::prepairToEndRender()
{
	//TODO(?)
}
void GLRenderer::postRender()
{
	//TODO(?)
}

std::shared_ptr<GLRenderer> GLRenderer::_glRenderer = nullptr;
