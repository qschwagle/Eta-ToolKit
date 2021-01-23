#pragma once

#include "widget.h"

namespace etk {
	class Image : public Widget {
	public:
		Image() = default;
		Image(const Image&) = delete;
		Image& operator=(const Image&) = delete;

		virtual ~Image();

		void Load(const std::wstring filePath);

		void Draw() override;
	private:
		int mImageHeight{ 0 };
		int mImageWidth{ 0 };
		int mChannels{ 0 };
		unsigned char* mImageData{ nullptr };
};
}