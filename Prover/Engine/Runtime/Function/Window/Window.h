#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Render/Interface/OpenGL/Viewport.h"
#include <iostream>

enum class RenderMode
{
	OpenGL, Vulkan
};

class Window {

public:
	Window() {
		if (_renderMode == RenderMode::OpenGL) {
			_viewportGL = GLViewport::getInstance();
		}
		else {
			std::cout << "Vulkan is null, please switch to OpenGL" << std::endl;
		}
	}
	~Window() {

	}
public:
	void setRenderMode(RenderMode mode) {
		_renderMode = mode;
	}
private:
	RenderMode _renderMode = RenderMode::OpenGL;
	std::shared_ptr<GLViewport> _viewportGL = nullptr;
};

#endif // !_WINDOW_H_
