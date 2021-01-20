#pragma once

#include "../text.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLText : public etk::renderer::Text {
public:
	void Draw() override;

};
}
}
}