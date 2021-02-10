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

void etk::Image::Load()
{
	mData->GetImageMetaData();
	SetInternalWidth(mData->GetImageWidth());
	SetInternalHeight(mData->GetImageHeight());
}

void etk::Image::Draw()
{
	if (!mImageRenderer) {
		mImageRenderer = GetDrawableFactory().lock()->CreateImage();
		mImageRenderer->LoadImage(mData->GetData(), mData->GetImageWidth(), mData->GetImageHeight(), mData->GetImageChannels());
	}
	mImageRenderer->SetPos(GetPosition().x, GetPosition().y);
	mImageRenderer->Draw(GetBox());
}

void etk::Image::SetPosition(const glm::vec2 position)
{
	etk::Widget::SetPosition(position);
}

void etk::Image::FromFileData::GetImageMetaData()
{
	FILE* file = fopen(mPath.c_str(), "rb");
	if (GetCurrentData()) stbi_image_free(GetCurrentData());
	int width, height;
	stbi_info_from_file(file, &width, &height, 0);
	SetImageWidth(width);
	SetImageHeight(height);
	fclose(file);
}

void etk::Image::FromFileData::GetImage()
{
	FILE* file = fopen(mPath.c_str(), "rb");
	FreeImage();
	int width, height, channels;
	SetData(stbi_load_from_file(file, &width, &height, &channels, 0));
	SetImageWidth(width);
	SetImageHeight(height);
	SetChannels(channels);
	fclose(file);
}

void etk::Image::FromFileData::FreeImage()
{
	if (GetCurrentData()) stbi_image_free(GetCurrentData());
	SetData(nullptr);
}
