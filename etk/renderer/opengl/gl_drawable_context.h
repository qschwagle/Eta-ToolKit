#pragma once

#include "../drawable_context.h"

namespace etk {
namespace renderer {
namespace opengl {
class GLDrawableContext : public etk::renderer::DrawableContext {
public:
	GLDrawableContext();
	void WindowInit(int width, int height) override;
	void Init() override;
	void Clear() override;
private:
};
}
}
}
