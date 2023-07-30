#ifndef _UNIFORMPROPERTIES_H_
#define _UNIFORMPROPERTIES_H_

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <map>

#define MAXDIRECTIONALLIGHTCOUNT 1000
#define MAXPOINTLIGHTCOUNT 100
#define MAXSPOTLIGHTCOUNT 100

class DirectionalLight;
class PointLight;
class SpotLight;

class UniformProperties {
public:
	void setUp();
	void clear();
	void setViewMatrix(const glm::mat4& viewMatrix);
	void setProjectionMatrix(const glm::mat4& projectionMatrix);
	void setCameraPosition(const glm::vec3& cameraPos);
public:
	void addDirectionalLight(std::shared_ptr<DirectionalLight> light);
	void addPointLight(std::shared_ptr<PointLight> light);
	void addSpotLight(std::shared_ptr<SpotLight> light);
	void removeDirectionalLight(std::shared_ptr<DirectionalLight> light);
	void removePointLight(std::shared_ptr<PointLight> light);
	void removeSpotLight(std::shared_ptr<SpotLight> light);
	void clearDirectionalLight();
	void clearPointLight();
	void clearSpotLight();
public:
	void updateSingleDirectionalLightBufferData(std::shared_ptr<DirectionalLight> light);
	void updateSinglePointLightBufferData(std::shared_ptr<PointLight> light);
	void updateSingleSpotLightBufferData(std::shared_ptr<SpotLight> light);
private:
	void setUpCommonProperties();
	void setUpDirectionalLightBuffer();
	void setUpPointLightBuffer();
	void setUpSpotLightBuffer();
private:
	void updateDirectionaLightBufferData();
	void updatePointLightBufferData();
	void updateSpotLightBufferData();
private:
	std::vector<std::shared_ptr<DirectionalLight>> _directionalLights;
	std::vector<std::shared_ptr<PointLight>> _pointLights;
	std::vector<std::shared_ptr<SpotLight>> _spotLights;
	std::map<std::shared_ptr<DirectionalLight>, int> _directionalLightsIndicesMap;
	std::map<std::shared_ptr<PointLight>, int> _pointLightsIndicesMap;
	std::map<std::shared_ptr<SpotLight>, int> _spotLightsIndicesMap;
private:
	unsigned int _UBOs[4];
};

#endif // !_UNIFORMPROPERTIES_H_