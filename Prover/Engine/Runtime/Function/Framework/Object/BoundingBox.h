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

	bool intersect(const BoundingBox& boundingBox) {
		return _aabb.intersect(boundingBox._aabb);
	}

	bool intersect(const glm::vec3& min, const glm::vec3& max) {
		return _aabb.intersect(min, max);
	}
private:
	AABB _aabb;
};
#endif // _AABB_H_
