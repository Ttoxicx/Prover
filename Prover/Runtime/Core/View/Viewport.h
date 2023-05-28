#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_
#include <glad/glad.h>
#include <glfw/glfw3.h>

class Renderer;

class Viewport {
public:
	Viewport();
	Viewport(int width, int height);
	~Viewport();
public:
	static Viewport* getInstance();
public:
	void exec();
public:
	void setRenderer(Renderer* renderer);
	void setViewPortSize(int width, int height);
	inline int getViewPortHeight() { return _windowHeight; };
	inline int getViewPortWidth() { return _windowWidth; };
private:
	void initViewPort();
	void initInputManager();
private:
	GLFWwindow* _window = nullptr;
	int _windowWidth = 800;
	int _windowHeight = 600;
private:
	Renderer* _renderer = nullptr;
private:
	static Viewport* _viewport;
};
#endif // !_VIEWPORT_H_
