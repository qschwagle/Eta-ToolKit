#pragma once

#include "../character.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLCharacter : public etk::renderer::Character {
public:
	void Draw() override;

};
}
}
}