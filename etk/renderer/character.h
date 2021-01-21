#pragma once

#include "drawable_object.h"

namespace etk {
namespace renderer {
class Character : public etk::renderer::DrawableObject {
public:
	Character(std::weak_ptr<DrawableContext> context) : etk::renderer::DrawableObject(context) {}
};
}
}