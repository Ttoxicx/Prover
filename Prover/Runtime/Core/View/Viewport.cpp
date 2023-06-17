#include "View/Viewport.h"
#include "Render/Renderer.h"
#include "Basic/InputManager.h"
#include "Basic/Camera.h"
#include <iostream>

Viewport::Viewport()
{
	initViewPort();
	initInputManager();
	initDefaultConfig();
}

Viewport::Viewport(int width, int height)
{ 
	_windowWidth = width; 
	_windowHeight = height; 
	initViewPort();
	initInputManager();
	initDefaultConfig();
}

std::shared_ptr<Viewport> Viewport::getInstance()
{
	if (_viewport == nullptr) {
		_viewport = std::make_shared<Viewport>();
	}
	return _viewport;
}

void framebuffer_windowsize_callback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height);
}

void Viewport::initViewPort()
{
	//��ʼ��GLFW
	glfwInit();
	//����OpenGL�汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//����Ϊ����ģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_window = glfwCreateWindow(_windowWidth, _windowHeight, "Prover", NULL, NULL);
	if (_window == NULL) {
		glfwTerminate();
		throw("Create Window Failed");
	}
	//����ǰ���ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(_window);
	//��GLAD��������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ���glfwGetProcAddress
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		throw("Failed to Initialize GLAD");
	}
	glViewport(0, 0, _windowWidth, _windowHeight);
	//ָ�����ڴ�С�ı�ʱ�Ļص�����
	glfwSetFramebufferSizeCallback(_window, framebuffer_windowsize_callback);
}

void Viewport::setRenderer(std::shared_ptr<Renderer> renderer)
{
	_renderer = renderer;
	if (renderer->getMainCamera() == nullptr) {
		renderer->setMainCamera(_defaultCamera);
	}
}

void Viewport::setViewPortSize(int width, int height) {
	_windowHeight = height;
	_windowWidth = width;
	glViewport(0, 0, _windowWidth, _windowHeight);
}

void Viewport::initInputManager()
{
	InputManager* inputManager = InputManager::getInstance().get();
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(_window, &InputManager::handleMouseXYCallBack);
	glfwSetScrollCallback(_window, &InputManager::handleMouseSrollCallBack);
}

void Viewport::initDefaultConfig()
{
	_defaultCamera = std::make_shared<Camera>();
	//���Ĭ���������
	auto cameraXY = [=](double xpos, double ypos) {
		if (_renderer->getMainCamera() != _defaultCamera) return;
		float speed = _defaultCamera->getCameraRotateSpeed();
		if (_isFisrtMove) {
			_mouseX = xpos;
			_mouseY = ypos;
			_isFisrtMove = false;
		}
		float deltaPitch = -(ypos - _mouseY) * deltaTime * speed;
		float deltaYaw = -(_mouseX - xpos) * deltaTime * speed;
		_mouseX = xpos;
		_mouseY = ypos;
		glm::vec3 rotation = _defaultCamera->getCameraRotation();
		float pitch = rotation.x;
		float yaw = rotation.y;
		rotation.x = glm::clamp<float>(pitch + deltaPitch, -89.f, 89.f);
		rotation.y = yaw + deltaYaw;
		_defaultCamera->setCameraRotation(rotation);
	};
	auto cameraFOV = [=](double xval, double yval) {
		if (_renderer->getMainCamera() != _defaultCamera) return;
		float speed = _defaultCamera->getCameraZoomSpeed();
		float fov = _defaultCamera->getCameraFOV();
		fov = glm::clamp(fov - float(yval * speed * deltaTime), 44.0f, 46.0f);
		_defaultCamera->setCameraFOV(fov);
	};
	auto CameraMoveForward = [=]() {
		if (_renderer->getMainCamera() != _defaultCamera) return;
		float speed = _defaultCamera->getCameraOffsetSpeed();
		glm::vec3 cameraloc = _defaultCamera->getCameraLocation();
		cameraloc += deltaTime * _defaultCamera->getCameraFrontVector() * speed;
		_defaultCamera->setCameraLocation(cameraloc);
	};
	auto CameraMoveBack = [=]() {
		if (_renderer->getMainCamera() != _defaultCamera) return;
		float speed = _defaultCamera->getCameraOffsetSpeed();
		glm::vec3 cameraloc = _defaultCamera->getCameraLocation();
		cameraloc -= deltaTime * _defaultCamera->getCameraFrontVector() * speed;
		_defaultCamera->setCameraLocation(cameraloc);
	};
	auto CameraMoveRight = [=]() {
		if (_renderer->getMainCamera() != _defaultCamera) return;
		float speed = _defaultCamera->getCameraOffsetSpeed();
		glm::vec3 cameraloc = _defaultCamera->getCameraLocation();
		cameraloc += deltaTime * _defaultCamera->getCameraRightVector() * speed;
		_defaultCamera->setCameraLocation(cameraloc);
	};
	auto CameraMoveLeft = [=]() {
		if (_renderer->getMainCamera() != _defaultCamera) return;
		float speed = _defaultCamera->getCameraOffsetSpeed();
		glm::vec3 cameraloc = _defaultCamera->getCameraLocation();
		cameraloc -= deltaTime * _defaultCamera->getCameraRightVector() * speed;
		_defaultCamera->setCameraLocation(cameraloc);
	};
	auto CameraMoveDown = [=]() {
		if (_renderer->getMainCamera() != _defaultCamera) return;
		float speed = _defaultCamera->getCameraOffsetSpeed();
		glm::vec3 cameraloc = _defaultCamera->getCameraLocation();
		cameraloc -= deltaTime * _defaultCamera->getCameraUpVector() * speed;
		_defaultCamera->setCameraLocation(cameraloc);
	};
	auto CameraMoveUp = [=]() {
		if (_renderer->getMainCamera() != _defaultCamera) return;
		float speed = _defaultCamera->getCameraOffsetSpeed();
		glm::vec3 cameraloc = _defaultCamera->getCameraLocation();
		cameraloc += deltaTime * _defaultCamera->getCameraUpVector() * speed;
		_defaultCamera->setCameraLocation(cameraloc);
	};
	//��ESC�˳�
	auto Exit = [=]() {
		if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(_window, true);
		}
	};
	auto input = InputManager::getInstance();
	input->addMouseXYCallBack(cameraXY);
	input->addMouseSrollCallBack(cameraFOV);
	input->addKeyMapping(InputKey::W, KeyState::PRESS, CameraMoveForward);
	input->addKeyMapping(InputKey::S, KeyState::PRESS, CameraMoveBack);
	input->addKeyMapping(InputKey::D, KeyState::PRESS, CameraMoveRight);
	input->addKeyMapping(InputKey::A, KeyState::PRESS, CameraMoveLeft);
	input->addKeyMapping(InputKey::Q, KeyState::PRESS, CameraMoveDown);
	input->addKeyMapping(InputKey::E, KeyState::PRESS, CameraMoveUp);
	input->addKeyMapping(InputKey::ESCAPE, KeyState::PRESS, Exit);
}

void Viewport::exec() {
	_startTime = glfwGetTime();
	while (!glfwWindowShouldClose(_window)) {
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		InputManager::handleKeyInput(_window);
		if (_renderer != nullptr) {
			_renderer->prepairToRender();
			_renderer->render();
		}
		glfwSwapBuffers(_window);
		float currentTime = glfwGetTime();
		deltaTime = currentTime - _startTime;
		_startTime = currentTime;
	}
	glfwTerminate();
}

std::shared_ptr<Viewport> Viewport::_viewport = nullptr;
float Viewport::deltaTime = 0.f;