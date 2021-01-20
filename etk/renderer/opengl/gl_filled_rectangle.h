#pragma once

#include "../filled_rectangle.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLFilledRectangle : public etk::renderer::FilledRectangle {
public:
	void Draw() override;
};

}
}
}