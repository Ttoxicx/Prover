#ifndef _MATERIAL_BASE_H_
#define _MATERIAL_BASE_H_

#include "Render/Shader/Shader.h"
#include <memory>

class MaterialBase {
protected:
	std::shared_ptr<Shader> shader;
};
#endif // !_MATERIAL_BASE_H_