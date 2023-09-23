#ifndef _MATERIAL_BASE_H_
#define _MATERIAL_BASE_H_

#include "Render/Interface/OpenGL/Shader.h"
#include <memory>

class GLMaterialBase {
protected:
	std::shared_ptr<GLShader> shader;
};
#endif // !_MATERIAL_BASE_H_