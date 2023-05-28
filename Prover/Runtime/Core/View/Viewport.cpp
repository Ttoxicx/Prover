#include "View/Viewport.h"
#include "Render/Renderer.h"
#include "Basic/InputManager.h"
#include <iostream>

Viewport::Viewport()
{
	initViewPort();
	initInputManager();
}

Viewport::Viewport(int width, int height)
{ 
	_windowWidth = width; 
	_windowHeight = height; 
	initViewPort();
	initInputManager();
}

Viewport::~Viewport()
{
	if (_viewport != nullptr) {
		delete _viewport;
		_viewport = nullptr;
	}
}

Viewport* Viewport::getInstance()
{
	if (_viewport == nullptr) {
		_viewport = new Viewport();
	}
	return _viewport;
}

void framebuffer_windowsize_callback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height);
}

void Viewport::initViewPort()
{
	glfwInit();//��ʼ��GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//����OpenGL�汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����Ϊ����ģʽ
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

void Viewport::setRenderer(Renderer* renderer)
{
	_renderer = renderer;
}

void Viewport::setViewPortSize(int width, int height) {
	_windowHeight = height;
	_windowWidth = width;
	glViewport(0, 0, _windowWidth, _windowHeight);
}

void Viewport::initInputManager()
{
	InputManager* inputManager = InputManager::getInstance();
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPosCallback(_window, &InputManager::handleMouseSrollCallBack);
	glfwSetScrollCallback(_window, &InputManager::handleMouseSrollCallBack);
}

void Viewport::exec() {
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
	}
	glfwTerminate();
}

Viewport* Viewport::_viewport = nullptr;