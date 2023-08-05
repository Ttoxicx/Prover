#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Render/Renderer.h"
#include "Basic/Geometry/Mesh.h"
#include "Render/Shader/Shader.h"
#include "View/Viewport.h"
#include "Input/InputManager.h"
#include "Basic/Camera.h"
#include "Render/Material/MeshMaterial.h"
#include "Basic/Light.h"
#include <iostream>

void loadTest(std::shared_ptr<Renderer> renderer) {
	//��Ⱦ����
	std::shared_ptr<MeshRenderUnit> mru = std::make_shared<MeshRenderUnit>();

	std::vector<glm::vec3> pointInfo = {
		glm::vec3(-0.5f,0.5f,-0.5f),
		glm::vec3(0.5f,0.5f,-0.5f),
		glm::vec3(0.5f,-0.5f,-0.5f),
		glm::vec3(-0.5f,-0.5f,-0.5f),
		glm::vec3(-0.5f,0.5f,0.5f),
		glm::vec3(0.5f,0.5f,0.5f),
		glm::vec3(0.5f,-0.5f,0.5f),
		glm::vec3(-0.5f,-0.5f,0.5f)
	};

	std::vector<glm::vec3> normalInfo = {
		glm::normalize(glm::vec3(-0.5f,0.5f,-0.5f)),
		glm::normalize(glm::vec3(0.5f,0.5f,-0.5f)),
		glm::normalize(glm::vec3(0.5f,-0.5f,-0.5f)),
		glm::normalize(glm::vec3(-0.5f,-0.5f,-0.5f)),
		glm::normalize(glm::vec3(-0.5f,0.5f,0.5f)),
		glm::normalize(glm::vec3(0.5f,0.5f,0.5f)),
		glm::normalize(glm::vec3(0.5f,-0.5f,0.5f)),
		glm::normalize(glm::vec3(-0.5f,-0.5f,0.5f))
	};

	/*std::vector<glm::vec3> normalInfo = {
		glm::vec3(0.f,0.f,1.f),
		glm::vec3(0.f,0.f,1.f),
		glm::vec3(0.f,0.f,1.f),
		glm::vec3(0.f,0.f,1.f),
		glm::vec3(0.f,0.f,1.f),
		glm::vec3(0.f,0.f,1.f),
		glm::vec3(0.f,0.f,1.f),
		glm::vec3(0.f,0.f,1.f)
	};*/

	std::vector<int> indicesInfo = {
		0,1,2,2,3,0,4,5,1,1,0,4,7,6,5,5,4,7,
		3,2,6,6,7,3,1,5,6,6,2,1,4,0,3,3,7,4
	};

	mru->mesh = std::make_shared<Mesh>();
	for (auto info : pointInfo) {
		mru->mesh->vertices.push_back(info);
	}
	for (auto info : normalInfo) {
		mru->mesh->normals.push_back(info);
	}
	for (auto info : indicesInfo) {
		mru->mesh->indices.push_back(info);
	}

	std::shared_ptr<MeshMaterial> mat = std::make_shared<MeshMaterial>();

	mat->setAmbientColor(glm::vec3(1.f, 1.f, 1.f));
	mat->setDiffuseColor(glm::vec3(1.f, 0.f, 0.f));
	mat->setSpecularColor(glm::vec3(1.f, 1.f, 1.f));
	mat->setMaxAmbient(glm::vec3(0.1f, 0.1f, 0.1f));
	mat->setMaxDiffuse(glm::vec3(0.9f, 0.9f, 0.9f));
	mat->setMaxSpecular(glm::vec3(1.f, 1.f, 1.f));

	mru->shader = mat->getShader();
	mru->renderSet = RenderSetting(
		RenderSetting::FaceCullMode::CullBack,
		RenderSetting::WireFrameMode::Off
	);
	renderer->addMeshRenderUnit(mru);
}

int main()
{
	auto viewport = Viewport::getInstance();
	auto renderer = std::make_shared<Renderer>();
	/*std::shared_ptr<DirectionalLight> light = std::make_shared<DirectionalLight>();
	light->lightColor = glm::vec4(1.f, 1.f, 1.f, 1.f);
	light->lightDir = glm::normalize(glm::vec4(0.f, 0.f, -1.f, 0.f));
	renderer->addDirectionalLight(light);*/
	std::shared_ptr<PointLight> light = std::make_shared<PointLight>();
	light->lightColor = glm::vec4(1.f, 1.f, 1.f, 1.f);
	light->lightPos = glm::normalize(glm::vec4(10.f, 10.f, 10.f, 0.f));
	renderer->addPointLight(light);
	viewport->setRenderer(renderer);
	loadTest(renderer);
	viewport->exec();
	return 0;
}