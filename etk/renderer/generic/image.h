#pragma once

#include "drawable_object.h"

namespace etk {
namespace renderer {
class Image : public DrawableObject {
public:
	Image() {};
	virtual	~Image() {}

	virtual void LoadImage(unsigned char* data, int width, int height, int channels) = 0;

	virtual void SetWidth(int width)=0;
	virtual void SetHeight(int height)=0;
	virtual float GetHeight() = 0;
	virtual float GetWidth() = 0;
private:
};
}
}