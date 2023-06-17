#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>

enum class ProjectionMode
{
	Perspective,
	Othographic
};

class Camera {
public:
	inline void setCameraFOV(float fov) { _fov = fov; }
	inline void setCameraAaspectRatio(float aspectRito) { _aspectRatio = aspectRito; }
	inline void setCameraFarPlane(float farPlane) { _farPlane = farPlane; }
	inline void setCameraNearPlane(float nearPlane) { _nearPlane = nearPlane; }
	inline void setCameraProjectionMode(ProjectionMode projectionMode) { _projectionMode = projectionMode; }
	inline void setCameraPixelMapSize(int width, int height) { _width = width; _height = height; }
	inline float getCameraFOV() { return _fov; }
	inline float getCameraAaspectRatio() { return _aspectRatio; }
	inline float getCameraFarPlane() { return _farPlane; }
	inline float getCameraNearPlane() { return _nearPlane; }
	inline int getCameraPixelMapWidth() { return _width; }
	inline int getCameraPixelMapHeight() { return _height; }
	inline glm::vec3 getCameraFrontVector() { return _frontVector; }
	inline glm::vec3 getCameraRightVector() { return _rightVector; }
	inline glm::vec3 getCameraUpVector() { return _upVector; }
	inline glm::mat4 getProjcetionMatrix() { return _projectionMatrix; }
	inline glm::mat4 getViewMatrix() { return _viewMatrix; }
	inline ProjectionMode getCameraProjectionMode() { return _projectionMode; }
public:
	inline void setCameraLocation(glm::vec3 location) { _location = location; }
	/*
	* 设置相机的欧拉角
	* x:Pitch y:Yaw z:Roll
	*/
	inline void setCameraRotation(glm::vec3 rotation) { _rotation = rotation; }
	inline glm::vec3 getCameraLocation() { return _location; }
	inline glm::vec3 getCameraRotation() { return _rotation; }
	inline void setCameraOffsetSpeed(float speed) { _offsetSpeed = _offsetSpeedUnit * speed; }
	inline void setCameraZoomSpeed(float speed) { _zoomSpeed = _zoomSpeedUnit * speed; }
	inline void setCameraRotateSpeed(float speed) { _rotateSpeed = _rotateSpeedUnit * speed; }
	inline float getCameraOffsetSpeed() { return _offsetSpeed; }
	inline float getCameraZoomSpeed() { return _zoomSpeed; }
	inline float getCameraRotateSpeed() { return _rotateSpeed; }
public:
	//相机更新
	void updateCameraInfo();
private:
	glm::vec3 _location = glm::vec3(0.f,0.f,10.f);
	glm::vec3 _rotation = glm::vec3(0.f, -90.f, 0.f);
	float _farPlane = 100.f;
	float _nearPlane = 0.1f;
	float _aspectRatio = 600.f / 800.f;
	float _fov = 45.f;
	float _width = 800.f;
	float _height = 600.f;
	glm::vec3 _frontVector = glm::vec3(0.f, 0.f, -1.f);
	glm::vec3 _rightVector = glm::vec3(1.f, 0.f, 0.f);
	glm::vec3 _upVector = glm::vec3(0, 1, 0);
	glm::mat4 _projectionMatrix = glm::mat4(1.f);
	glm::mat4 _viewMatrix = glm::mat4(1.f);
	ProjectionMode _projectionMode = ProjectionMode::Perspective;
private:
	float _rotateSpeedUnit = 20;
	float _zoomSpeedUnit = 40;
	float _offsetSpeedUnit = 20;
	float _rotateSpeed = _rotateSpeedUnit;
	float _zoomSpeed = _zoomSpeedUnit;
	float _offsetSpeed = _offsetSpeedUnit;
};
#endif // !_CAMERA_H_
