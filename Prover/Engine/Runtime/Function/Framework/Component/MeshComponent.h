#ifndef _MESHCOMPONENT_H_
#define _MESHCOMPONENT_H_

#include "Framework/Component/Component.h"
#include <list>
#include <memory>

class GLMeshRenderUnit;

class MeshComponent :public Component {
public:
	virtual void tickComponent(double deltaTime) override;
private:
	std::list<std::shared_ptr<GLMeshRenderUnit>> _meshes;
};

#endif // !_MESHCOMPONENT_H_
