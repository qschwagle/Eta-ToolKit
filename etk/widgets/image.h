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

		void Load();

		void Draw() override;

		void Invalidate() override {
			mImageRenderer = nullptr;
		}

		void SetPosition(const glm::vec2 position) override;

		class Data {
		public:
			virtual void GetImageMetaData() {};
			virtual void GetImage() {}

			void Clear() {
				mImageHeight = -1;
				mImageWidth = -1;
				mChannels = -1;
				FreeImage();
			}

			int GetImageHeight() {
				if (mImageHeight == -1) GetImageMetaData();
				return mImageHeight;
			}

			int GetImageWidth() {
				if (mImageWidth == -1) GetImageMetaData();
				return mImageWidth;
			}

			int GetImageChannels() {
				if (mChannels == -1) GetImage();
				return mChannels;
			}

			unsigned char* GetData() {
				if (!mImageData) GetImage();
				return mImageData;
			}

			virtual void FreeImage() {}
		protected:

			unsigned char* GetCurrentData() {
				return mImageData;
			}
			void SetImageHeight(int h) {
				mImageHeight = h;
			}

			void SetImageWidth(int w) {
				mImageWidth = w;
			}

			void SetChannels(int c) {
				mChannels = c;
			}

			void SetData(unsigned char* d) {
				mImageData = d;
			}
		private:
			int mImageHeight{ -1 };
			int mImageWidth{ -1 };
			int mChannels{ -1 };
			unsigned char* mImageData{ nullptr };
		};

		class FromFileData : public Data {
		public:
			FromFileData(std::string path) : mPath{ path } {};
			void GetImageMetaData() override;
			void GetImage() override;

			void FreeImage() override;
		private:
			std::string mPath;
		};

		void SetData(std::shared_ptr<Data> d) {
			mData = d;
		}
	private:
		std::shared_ptr<Data> mData;
		unsigned char* mImageData{ nullptr };

		std::unique_ptr<etk::renderer::Image> mImageRenderer;
};
}