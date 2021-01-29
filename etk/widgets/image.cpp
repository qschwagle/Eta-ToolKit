#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <fstream>

#include <locale>
#include <codecvt>

etk::Image::~Image()
{
	if (mImageData) stbi_image_free(mImageData);
}

void etk::Image::Load(const std::wstring filePath)
{
	setlocale(LC_ALL, "");

	auto converter = std::wstring_convert<std::codecvt_utf8<wchar_t>>();
	std::string mbs = converter.to_bytes(filePath);
	FILE* file = fopen(mbs.c_str(), "rb");
	if (mImageData) stbi_image_free(mImageData);
	mImageData  = stbi_load_from_file(file, &mImageWidth, &mImageHeight, &mChannels, 0);
	SetInternalWidth(mImageWidth);
	SetInternalHeight(mImageHeight);
	fclose(file);
}

void etk::Image::Draw()
{
	if (!mImageRenderer) {
		mImageRenderer = GetDrawableFactory().lock()->CreateImage();
		mImageRenderer->LoadImage(mImageData, mImageWidth, mImageHeight, mChannels);
	}
	mImageRenderer->SetPos(GetPosition().x, GetPosition().y);
	mImageRenderer->Draw(GetBox().lock()->GetShift());
}

void etk::Image::SetPosition(const glm::vec2 position)
{
	etk::Widget::SetPosition(position);
}
