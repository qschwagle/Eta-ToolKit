#pragma once

#include "../character.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLCharacter : public etk::renderer::Character {
public:
	GLCharacter(std::weak_ptr<etk::renderer::DrawableContext> context) : etk::renderer::Character(context) {}
	void Draw() override;

};
}
}
}