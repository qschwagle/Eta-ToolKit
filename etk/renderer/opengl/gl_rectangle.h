#pragma once

#include "../rectangle.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLRectangle : public etk::renderer::Rectangle {
public:
	void Draw() override;
};
}
}
}