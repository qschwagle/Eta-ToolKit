#pragma once

#include "drawable_object.h"

namespace etk {
namespace renderer {
class Rectangle : public DrawableObject {
public:
	Rectangle(std::weak_ptr<DrawableContext> context) : DrawableObject(context) {}

};
}
}
