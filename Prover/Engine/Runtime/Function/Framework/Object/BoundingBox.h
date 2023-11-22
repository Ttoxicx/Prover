#ifndef _BOUNDING_BOX_H_
#define _BOUNDING_BOX_H_

#include "Math/AABB.h"
#include <glm/glm.hpp>

class BoundingBox {
public:
	BoundingBox() {

	}

	BoundingBox(const glm::vec3& min, const glm::vec3& max) {
		_aabb.setMinMax(min, max);
	}

	BoundingBox(const BoundingBox& boundingBox) {
		_aabb = boundingBox._aabb;
	}

public:

	const AABB& aabb() const {
		return _aabb;
	}

private:
	AABB _aabb;
};
#endif // _AABB_H_
