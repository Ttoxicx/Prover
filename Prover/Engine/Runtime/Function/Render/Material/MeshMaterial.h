#ifndef _MESH_MATERIAL_H_
#define _MESH_MATERIAL_H_

#include "Render/Material/MaterialBase.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class MeshMaterial :public MaterialBase {
public:
	MeshMaterial() {
		shader = std::make_shared<Shader>(
			"../../../../Prover/Engine/Runtime/Function/Render/Shader/SL/GLSL/IlluminationModel/BlinnPhong.vert",
			"../../../../Prover/Engine/Runtime/Function/Render/Shader/SL/GLSL/IlluminationModel/BlinnPhong.frag"
			);
		shader->setParameters3f("ambientColor", _ambientColor);
		shader->setParameters3f("diffuseColor", _diffuseColor);
		shader->setParameters3f("specularColor", _specularColor);
		shader->setParameters3f("maxAmbient", _maxAmbient);
		shader->setParameters3f("maxDiffuse", _maxDiffuse);
		shader->setParameters3f("maxSpecular", _maxSpecular);
		shader->setParameters1b("useTexture", _useTexture);
		shader->setParameters1f("shininess", _shininess);
		shader->setParametersMat4f("modelMatrix", _modelMatrix);
		shader->setParametersMat3f("normalMatrix", glm::mat3(glm::transpose(glm::inverse(_modelMatrix))));
	}
public:
	void setAmbientColor(const glm::vec3& ambientColor) {
		_ambientColor = ambientColor;
		shader->setParameters3f("ambientColor", ambientColor);
	}
	void setDiffuseColor(const glm::vec3& diffuseColor) {
		_diffuseColor = diffuseColor;
		shader->setParameters3f("diffuseColor", diffuseColor);
	}
	void setSpecularColor(const glm::vec3& specularColor) {
		_specularColor = specularColor;
		shader->setParameters3f("specularColor", specularColor);
	}
	void setMaxAmbient(const glm::vec3& maxAmbient) {
		_maxAmbient = maxAmbient;
		shader->setParameters3f("maxAmbient", maxAmbient);
	}
	void setMaxDiffuse(const glm::vec3& maxDiffuse) {
		_maxDiffuse = maxDiffuse;
		shader->setParameters3f("maxDiffuse", maxDiffuse);
	}
	void setMaxSpecular(const glm::vec3& maxSpecular) {
		_maxSpecular = maxSpecular;
		shader->setParameters3f("maxSpecular", maxSpecular);
	}
	void setUseTexture(bool useTexture) {
		_useTexture = useTexture;
		shader->setParameters1b("useTexture", useTexture);
	}
	void setShiness(float shininess) {
		_shininess = shininess;
		shader->setParameters1f("shininess", shininess);
	}
	void setModelMatrix(glm::mat4 modelMatrix) {
		_modelMatrix = modelMatrix;
		shader->setParametersMat4f("modelMatrix", modelMatrix);
	}
	void setNormalMatrix(glm::mat3 normalMatrix) {
		_normalMatrix = normalMatrix;
		shader->setParametersMat3f("normalMatrix", normalMatrix);
	}
	std::shared_ptr<Shader> getShader() {
		return shader;
	}
private:
	glm::vec3 _ambientColor = glm::vec3(1.f, 1.f, 1.f);
	glm::vec3 _diffuseColor = glm::vec3(1.f, 1.f, 1.f);
	glm::vec3 _specularColor = glm::vec3(1.f, 1.f, 1.f);
	glm::vec3 _maxAmbient = glm::vec3(0.1f, 0.1f, 0.1f);
	glm::vec3 _maxDiffuse = glm::vec3(0.9f, 0.9f, 0.9f);
	glm::vec3 _maxSpecular = glm::vec3(1.f, 1.f, 1.f);
	//todo Texture
	/*sampler2D ambinetTex;
	sampler2D diffuseTex;
	sampler2D specularTex;
	sampler2D normalTex;*/
	float _shininess = 32.0f;
	bool _useTexture = false;
	
	//±‰ªªœ‡πÿ
	glm::mat4 _modelMatrix = glm::mat4(1.0f);
	glm::mat4 _normalMatrix = glm::mat3(1.0f);

};

#endif // !_MESH_MATERIAL_H_
