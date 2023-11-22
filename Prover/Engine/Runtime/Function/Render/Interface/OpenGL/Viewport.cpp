#include "Render/Interface/OpenGL/Viewport.h"
#include "Render/Interface/OpenGL/Renderer.h"
#include "Input/InputManager.h"
#include "Render/Camera/Camera.h"
#include <iostream>

GLViewport::GLViewport()
{
	initViewport();
	initRenderer();
	initInputManager();
	initDefaultConfig();
}

GLViewport::GLViewport(int width, int height)
{ 
	_windowWidth = width; 
	_windowHeight = height; 
	initViewport();
	initInputManager();
	initDefaultConfig();
}

std::shared_ptr<GLViewport> GLViewport::getInstance()
{
	if (_viewport == nullptr) {
		_viewport = std::make_shared<GLViewport>();
	}
	return _viewport;
}

void framebuffer_windowsize_callback(GLFWwindow* window, int width, int height) 
{
	GLViewport::getInstance()->setViewportSize(width, height);
}

void GLViewport::initViewport()
{
	//init GLFW
	glfwInit();
	//set OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//set OpenGL mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_window = glfwCreateWindow(_windowWidth, _windowHeight, "Prover", NULL, NULL);
	if (_window == NULL) {
		glfwTerminate();
		throw("Create Window Failed");
	}
	//set main context
	glfwMakeContextCurrent(_window);
	//load opengl function address
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		throw("Failed to Initialize GLAD");
	}
	glViewport(0, 0, _windowWidth, _windowHeight);
	//framebuffer callback
	glfwSetFramebufferSizeCallback(_window, framebuffer_windowsize_callback);
}

void GLViewport::initRenderer()
{
	_renderer = GLRenderer::getInstance();
}

void GLViewport::setViewportSize(int width, int height) {
	_windowHeight = height;
	_windowWidth = width;
	glViewport(0, 0, _windowWidth, _windowHeight);
	auto camera = _renderer->getMainCamera();
	if (camera) {
		camera->setCameraAaspectRatio(float(width) / float(height));
		camera->setCameraPixelMapSize(width, height);
	}
}

void GLViewport::initInputManager()
{
	InputManager::getInstance();
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(_window, &InputManager::handleMouseXYCallBack);
	glfwSetScrollCallback(_window, &InputManager::handleMouseSrollCallBack);
}

void GLViewport::initDefaultConfig()
{
	//default camera control
	auto cameraXY = [=](double xpos, double ypos) {
		if (glfwGetInputMode(_window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) return;
		auto camera = _renderer->getMainCamera();
		float speed = camera->getCameraRotateSpeed();
		if (_isFisrtMove) {
			_mouseX = xpos;
			_mouseY = ypos;
			_isFisrtMove = false;
		}
		float deltaPitch = -(ypos - _mouseY) * deltaTime * speed;
		float deltaYaw = -(_mouseX - xpos) * deltaTime * speed;
		_mouseX = xpos;
		_mouseY = ypos;
		glm::vec3 rotation = _renderer->getMainCamera()->getCameraRotation();
		float pitch = rotation.x;
		float yaw = rotation.y;
		rotation.x = glm::clamp<float>(pitch + deltaPitch, -89.f, 89.f);
		rotation.y = yaw + deltaYaw;
		camera->setCameraRotation(rotation);
	};
	auto cameraFOV = [=](double xval, double yval) {
		auto camera = _renderer->getMainCamera();
		float speed = camera->getCameraZoomSpeed();
		float fov = camera->getCameraFOV();
		fov = glm::clamp(fov - float(yval * speed * deltaTime), 44.0f, 46.0f);
		camera->setCameraFOV(fov);
	};
	auto CameraMoveForward = [=]() {
		auto camera = _renderer->getMainCamera();
		float speed = camera->getCameraOffsetSpeed();
		glm::vec3 cameraloc = camera->getCameraLocation();
		cameraloc += deltaTime * camera->getCameraFrontVector() * speed;
		camera->setCameraLocation(cameraloc);
	};
	auto CameraMoveBack = [=]() {
		auto camera = _renderer->getMainCamera();
		float speed = camera->getCameraOffsetSpeed();
		glm::vec3 cameraloc = camera->getCameraLocation();
		cameraloc -= deltaTime * camera->getCameraFrontVector() * speed;
		camera->setCameraLocation(cameraloc);
	};
	auto CameraMoveRight = [=]() {
		auto camera = _renderer->getMainCamera();
		float speed = camera->getCameraOffsetSpeed();
		glm::vec3 cameraloc = camera->getCameraLocation();
		cameraloc += deltaTime * camera->getCameraRightVector() * speed;
		camera->setCameraLocation(cameraloc);
	};
	auto CameraMoveLeft = [=]() {
		auto camera = _renderer->getMainCamera();
		float speed = camera->getCameraOffsetSpeed();
		glm::vec3 cameraloc = camera->getCameraLocation();
		cameraloc -= deltaTime * camera->getCameraRightVector() * speed;
		camera->setCameraLocation(cameraloc);
	};
	auto CameraMoveDown = [=]() {
		auto camera = _renderer->getMainCamera();
		float speed = camera->getCameraOffsetSpeed();
		glm::vec3 cameraloc = camera->getCameraLocation();
		cameraloc -= deltaTime * camera->getCameraUpVector() * speed;
		camera->setCameraLocation(cameraloc);
	};
	auto CameraMoveUp = [=]() {
		auto camera = _renderer->getMainCamera();
		float speed = camera->getCameraOffsetSpeed();
		glm::vec3 cameraloc = camera->getCameraLocation();
		cameraloc += deltaTime * camera->getCameraUpVector() * speed;
		camera->setCameraLocation(cameraloc);
	};
	//escape
	auto Exit = [=]() {
		if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(_window, true);
		}
	};
	//show cursor
	auto ShowCursor = [=]() {
		if (glfwGetInputMode(_window, GLFW_CURSOR) != GLFW_CURSOR_NORMAL) {
			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	};
	//hide cursor
	auto HideCursor = [=]() {
		if (glfwGetInputMode(_window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED) {
			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
	input->addKeyMapping(InputKey::LEFT_ALT, KeyState::PRESS, ShowCursor);
	input->addKeyMapping(InputKey::LEFT_ALT, KeyState::RELEASE, HideCursor);
	input->addKeyMapping(InputKey::ESCAPE, KeyState::PRESS, Exit);
}

void GLViewport::exec() {
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

std::shared_ptr<GLViewport> GLViewport::_viewport = nullptr;
float GLViewport::deltaTime = 0.f;