#include "Render/Renderer.h"
#include "Render/DataClass/Mesh.h"
#include "Render/DataClass/Line.h"
#include "Render/DataClass/Point.h"
#include "Render/Shader/Shader.h"
#include "Basic/Camera.h"
#include "glad/glad.h"

GeometryRenderBuffer* Renderer::setUpMeshGeometryRenderBuffer(Mesh* mesh)
{
	unsigned int* VAO = new unsigned int;
	unsigned int* VBO = new unsigned int;
	unsigned int* EBO = new unsigned int;
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);
	glBindVertexArray(*VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
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
	glBufferSubData(GL_ARRAY_BUFFER, pointOffset, sizeofPoints, &(mesh->vertices[0]));
	glBufferSubData(GL_ARRAY_BUFFER, normalOffset, sizeofNormals, &(mesh->normals[0]));
	glBufferSubData(GL_ARRAY_BUFFER, texOffset, sizeofTex, &(mesh->texCoords[0]));
	glBufferSubData(GL_ARRAY_BUFFER, tangentOffset, sizeofTangents, &(mesh->tangents[0]));
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeofIndices, &(mesh->indices[0]));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)pointOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)normalOffset);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)texOffset);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)tangentOffset);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glBindVertexArray(0);
	GeometryRenderBuffer* buffer = new GeometryRenderBuffer;
	buffer->VAO = VAO;
	buffer->VBO = VBO;
	buffer->EBO = EBO;
	return buffer;
}
GeometryRenderBuffer* Renderer::setUpLineGeometryRenderBuffer(Line* line)
{
	unsigned int* VAO = new unsigned int;
	unsigned int* VBO = new unsigned int;
	unsigned int* EBO = new unsigned int;
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);
	glBindVertexArray(*VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	unsigned int sizeofPoints = line->vertices.size() * sizeof(glm::vec3);
	unsigned int sizeofIndices = line->indices.size() * sizeof(unsigned int);
	unsigned int pointOffset = 0;
	glBufferData(GL_ARRAY_BUFFER, sizeofPoints, NULL, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofIndices, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, pointOffset, sizeofPoints, &(line->vertices[0]));
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeofIndices, &(line->indices[0]));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)pointOffset);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	GeometryRenderBuffer* buffer = new GeometryRenderBuffer;
	buffer->VAO = VAO;
	buffer->VBO = VBO;
	buffer->EBO = EBO;
	return buffer;
}
GeometryRenderBuffer* Renderer::setUpPointGeometryRenderBuffer(Point* point)
{
	unsigned int* VAO = new unsigned int;
	unsigned int* VBO = new unsigned int;
	unsigned int* EBO = new unsigned int;
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);
	glBindVertexArray(*VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	unsigned int sizeofPoints = point->vertices.size() * sizeof(glm::vec3);
	for (int i = 0; i < point->vertices.size(); ++i) {
		point->indices.push_back(i);
	}
	unsigned int pointOffset = 0;
	glBufferData(GL_ARRAY_BUFFER, sizeofPoints, NULL, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, point->indices.size() * sizeof(unsigned int), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, pointOffset, sizeofPoints, &(point->vertices[0]));
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeofPoints, &(point->indices[0]));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)pointOffset);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	GeometryRenderBuffer* buffer=new GeometryRenderBuffer;
	buffer->VAO = VAO;
	buffer->VBO = VBO;
	buffer->EBO = EBO;
	return buffer;
}
void Renderer::deleteGeometryRenderBuffer(GeometryRenderBuffer* buffer)
{
	glDeleteBuffers(1, buffer->VBO);
	glDeleteBuffers(1, buffer->EBO);
	glDeleteVertexArrays(1, buffer->VAO);
	delete buffer->VBO;
	delete buffer->EBO;
	delete buffer->VAO;
}

void Renderer::drawMesh(MeshRenderUnit* mru)
{
	auto rendersetting = mru->renderSet;
	if (rendersetting.getFaceCullMode() == RenderSetting::FaceCullMode::CullFront) {
		glCullFace(GL_FRONT);
	}
	if (rendersetting.getFaceCullMode() == RenderSetting::FaceCullMode::CullBack) {
		glCullFace(GL_BACK);
	}
	if (rendersetting.getFaceCullMode() == RenderSetting::FaceCullMode::Off) {
		glDisable(GL_CULL_FACE);
	}
	if (rendersetting.getWireFrameMode() == RenderSetting::WireFrameMode::On) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	auto buffer = _meshRenderMapping.at(mru);
	glUseProgram(mru->shader->getShaderId());
	glBindVertexArray(*(buffer->VAO));
	glDrawElements(GL_TRIANGLES, mru->mesh->indices.size(), GL_UNSIGNED_INT, (void*)0);
	updateShaderCommonAttribute(mru->shader);
	glBindVertexArray(0);
	glUseProgram(0);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::drawLine(LineRenderUnit* lru)
{
	auto buffer = _lineRenderMapping.at(lru);
	glBindVertexArray(*(buffer->VAO));
	glUseProgram(lru->shader->getShaderId());
	updateShaderCommonAttribute(lru->shader);
	glBindVertexArray(0);
	glUseProgram(0);
	glDrawElements(GL_LINE, lru->line->indices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

void Renderer::drawPoint(PointRenderUnit* pru)
{
	auto buffer = _pointRenderMapping.at(pru);
	glBindVertexArray(*(buffer->VAO));
	glUseProgram(pru->shader->getShaderId());
	updateShaderCommonAttribute(pru->shader);
	glBindVertexArray(0);
	glUseProgram(0);
	glDrawElements(GL_POINT, pru->point->indices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

void Renderer::setViewMatrix(Shader* shader)
{
	if (_mainCamera != nullptr) {
		shader->setParametersMat4f("viewMatrix", _mainCamera->getViewMatrix());
	}
	else {
		shader->setParametersMat4f("viewMatrix", glm::mat4(1.0f));
	}
}
void Renderer::setProjectionMatrix(Shader* shader)
{
	if (_mainCamera != nullptr) {
		shader->setParametersMat4f("projectionMatrix", _mainCamera->getViewMatrix());
	}
	else {
		shader->setParametersMat4f("projectionMatrix", glm::mat4(1.0f));
	}
}

void Renderer::setCameraPosition(Shader* shader) {
	if (_mainCamera != nullptr) {
		shader->setParameters3f("cameraPosition", _mainCamera->getCameraLocation());
	}
	else {
		shader->setParameters3f("cameraPosition", glm::vec3(0.f));
	}
}

void Renderer::updateShaderCommonAttribute(Shader* shader)
{
	setProjectionMatrix(shader);
	setViewMatrix(shader);
	setCameraPosition(shader);
}

void Renderer::prepairToRender()
{
	for (auto value : _meshRenderUnitsRemove) {
		auto buffer = _meshRenderMapping.at(value);
		deleteGeometryRenderBuffer(buffer);
		_meshRenderMapping.erase(value);
	}
	for (auto value : _lineRenderUnitsRemove) {
		auto buffer = _lineRenderMapping.at(value);
		deleteGeometryRenderBuffer(buffer);
		_lineRenderMapping.erase(value);
	}
	for (auto value : _pointRenderUnitsRemove) {
		auto buffer = _pointRenderMapping.at(value);
		deleteGeometryRenderBuffer(buffer);
		_pointRenderMapping.erase(value);
	}
	for (auto value : _meshRenderUnitsAdd) {
		auto val = _meshRenderMapping.find(value);
		if (val == _meshRenderMapping.end()) {
			auto buffer = setUpMeshGeometryRenderBuffer(value->mesh);
			_meshRenderMapping.emplace(value, buffer);
		}
	}
	for (auto value : _lineRenderUnitsAdd) {
		auto val = _lineRenderMapping.find(value);
		if (val == _lineRenderMapping.end()) {
			auto buffer = setUpLineGeometryRenderBuffer(value->line);
			_lineRenderMapping.emplace(value, buffer);
		}
	}
	for (auto value : _pointRenderUnitsAdd) {
		auto val = _pointRenderMapping.find(value);
		if (val == _pointRenderMapping.end()) {
			auto buffer = setUpPointGeometryRenderBuffer(value->point);
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
void Renderer::render()
{
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
void Renderer::prepairToEndRender()
{
	//TODO(?)
}
void Renderer::postRender()
{
	//TODO(?)
}