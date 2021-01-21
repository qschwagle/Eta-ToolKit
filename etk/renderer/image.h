#pragma once

#include "drawable_object.h"

namespace etk {
namespace renderer {
class Image : public DrawableObject {
public:
	Image(std::weak_ptr<DrawableContext> context) : DrawableObject(context) {}
private:
};
}
}