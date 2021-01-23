#pragma once

#include "../generic/window_background.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLWindowBackground : public etk::renderer::WindowBackground {
public:
	void Draw() override;

};
}
}
}