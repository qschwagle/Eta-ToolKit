#pragma once

#include "../image.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLImage : public etk::renderer::Image {
public:
	void Draw() override;

};
}
}
}