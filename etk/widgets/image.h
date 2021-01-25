#pragma once

#include "widget.h"

#include "../renderer/generic/image.h"

namespace etk {
	class Image : public Widget {
	public:
		Image() = default;
		Image(const Image&) = delete;
		Image& operator=(const Image&) = delete;

		virtual ~Image();

		void Load(const std::wstring filePath);

		void Draw(const glm::vec2& eye) override;

		void Invalidate() override {
			mImageRenderer = nullptr;
		}

		void SetPosition(const glm::vec2 position) override;
	private:
		int mImageHeight{ 0 };
		int mImageWidth{ 0 };
		int mChannels{ 0 };
		unsigned char* mImageData{ nullptr };

		std::unique_ptr<etk::renderer::Image> mImageRenderer;
};
}