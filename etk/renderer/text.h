#pragma once
#include "drawable_object.h"

namespace etk {
namespace renderer {
class Text : public DrawableObject {
public:
	Text(std::weak_ptr<DrawableContext> context) : DrawableObject(context) {}
};
}
}