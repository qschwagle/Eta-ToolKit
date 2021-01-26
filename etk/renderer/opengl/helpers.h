#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace etk {
namespace renderer {
namespace opengl {
inline glm::mat4 CreateOrtho(const glm::vec2& eye, float width, float height) {
	return glm::ortho(eye.x, eye.x + width, -1.0f * (height + eye.y), -1.0f * eye.y, 0.1f, 100.0f);
}
}
}
}