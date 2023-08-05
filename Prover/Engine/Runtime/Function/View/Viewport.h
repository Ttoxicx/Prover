#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <memory>

class Renderer;
class Camera;

class Viewport {
public:
	Viewport();
	Viewport(int width, int height);
	~Viewport() {
	}
public:
	static std::shared_ptr<Viewport> getInstance();
	static float deltaTime;
public:
	void exec();
public:
	void setRenderer(std::shared_ptr<Renderer> renderer);
	void setViewportSize(int width, int height);
	inline int getViewportHeight() { return _windowHeight; };
	inline int getViewportWidth() { return _windowWidth; };
private:
	void initViewport();
	void initInputManager();
	void initDefaultConfig();
private:
	GLFWwindow* _window;
	int _windowWidth = 800;
	int _windowHeight = 600;
private:
	std::shared_ptr<Renderer> _renderer;
	std::shared_ptr<Camera> _defaultCamera;
private:
	float _mouseX = 0.f;
	float _mouseY = 0.f;
	bool _isFisrtMove = true;
	float _startTime = 0.f;
private:
	static std::shared_ptr<Viewport> _viewport;
};
#endif // !_VIEWPORT_H_
