#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Render/Renderer.h"
#include "Geometry/Mesh.h"
#include "Render/Shader/Shader.h"
#include "View/Viewport.h"
#include "Basic/InputManager.h"
#include "Basic/Camera.h"
#include <iostream>

int main()
{
	auto viewport = Viewport::getInstance();
	auto renderer = std::make_shared<Renderer>();
	viewport->setRenderer(renderer);
	std::shared_ptr<MeshRenderUnit> mru=std::make_unique<MeshRenderUnit>();
	
	mru->mesh = std::make_shared<Mesh>();
	mru->mesh->vertices.push_back(glm::vec3(0.f, 1.f, 0.f));
	mru->mesh->vertices.push_back(glm::vec3(-1.f, -1.f, 0.f));
	mru->mesh->vertices.push_back(glm::vec3(1.f, -1.f, 0.f));
	mru->mesh->normals.push_back(glm::vec3(0.f, 1.f, 0.f));
	mru->mesh->normals.push_back(glm::vec3(-1.f, -1.f, 0.f));
	mru->mesh->normals.push_back(glm::vec3(1.f, -1.f, 0.f));
	mru->mesh->tangents.push_back(glm::vec3(0.f, 1.f, 0.f));
	mru->mesh->tangents.push_back(glm::vec3(-1.f, -1.f, 0.f));
	mru->mesh->tangents.push_back(glm::vec3(1.f, -1.f, 0.f));
	mru->mesh->texCoords.push_back(glm::vec2(1.f, 0.f));
	mru->mesh->texCoords.push_back(glm::vec2(-1.f, 0.f));
	mru->mesh->texCoords.push_back(glm::vec2(-1.f, 0.f));
	mru->mesh->indices.push_back(0);
	mru->mesh->indices.push_back(1);
	mru->mesh->indices.push_back(2);
	mru->shader = std::make_shared<Shader>(
		"../../../../Prover/Runtime/Core/Render/Shader/SL/GLSL/SingleColor.vert",
		"../../../../Prover/Runtime/Core/Render/Shader/SL/GLSL/SingleColor.frag"
		);
	mru->renderSet = RenderSetting(
		RenderSetting::FaceCullMode::Off,
		RenderSetting::WireFrameMode::Off
	);
	std::shared_ptr<MeshRenderUnit> mru2 = std::make_unique<MeshRenderUnit>();
	mru2->mesh = std::make_shared<Mesh>();
	glm::vec3 offset = glm::vec3(0.7f, 0.7f, 0.7f);
	mru2->mesh->vertices.push_back(glm::vec3(0.f, 1.f, 0.f) * 0.2f + offset);
	mru2->mesh->vertices.push_back(glm::vec3(-1.f, -1.f, 0.f) * 0.2f + offset);
	mru2->mesh->vertices.push_back(glm::vec3(1.f, -1.f, 0.f) * 0.2f + offset);
	mru2->mesh->normals.push_back(glm::vec3(0.f, 1.f, 0.f) * 0.2f + offset);
	mru2->mesh->normals.push_back(glm::vec3(-1.f, -1.f, 0.f) * 0.2f + offset);
	mru2->mesh->normals.push_back(glm::vec3(1.f, -1.f, 0.f) * 0.2f + offset);
	mru2->mesh->tangents.push_back(glm::vec3(0.f, 1.f, 0.f) * 0.2f + offset);
	mru2->mesh->tangents.push_back(glm::vec3(-1.f, -1.f, 0.f) * 0.2f + offset);
	mru2->mesh->tangents.push_back(glm::vec3(1.f, -1.f, 0.f) * 0.2f + offset);
	mru2->mesh->texCoords.push_back(glm::vec2(1.f, 0.f));
	mru2->mesh->texCoords.push_back(glm::vec2(-1.f, 0.f));
	mru2->mesh->texCoords.push_back(glm::vec2(-1.f, 0.f));
	mru2->mesh->indices.push_back(0);
	mru2->mesh->indices.push_back(1);
	mru2->mesh->indices.push_back(2);
	mru2->shader = std::make_shared<Shader>(
		"../../../../Prover/Runtime/Core/Render/Shader/SL/GLSL/SingleColor.vert",
		"../../../../Prover/Runtime/Core/Render/Shader/SL/GLSL/SingleColor.frag"
		);
	mru2->renderSet = RenderSetting(
		RenderSetting::FaceCullMode::Off,
		RenderSetting::WireFrameMode::Off
	);
	if (!mru2->shader->isShaderBuildSuccessful()) {
		mru2->shader->getShaderCondition();
	}
	renderer->addMeshRenderUnit(mru);
	renderer->addMeshRenderUnit(mru2);
	//¿ØÖÆ²âÊÔ
	auto input = InputManager::getInstance();
	auto fun = [&mru2]() {
		mru2->shader->setParameters4f("color", glm::vec4(1.0f, 0.f, 0.f, 1.f));
	};
	auto fun1 = [&mru]() {
		mru->shader->setParameters4f("color", glm::vec4(0.0f, 1.f, 0.f, 1.f));
	};
	input->addKeyMapping(InputKey::I, KeyState::PRESS, fun);
	input->addKeyMapping(InputKey::O, KeyState::PRESS, fun1);

	viewport->exec();

	return 0;
}