#pragma once

#include <memory>

#include "gl_drawable_context.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLObject {
public:
	GLObject(std::weak_ptr<GLDrawableContext> context) : mContext(context) {}
protected:
	std::weak_ptr<GLDrawableContext> GetContext() const { return mContext; }
private:
	std::weak_ptr<GLDrawableContext> mContext;
};
}
}
}
