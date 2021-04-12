#include "book.h"

etk::font_rendering::FontBook::FontBook()
{
}

etk::font_rendering::FontBook::~FontBook()
{
	for (auto i : mFontAtlases) {
		delete i.second;
	}
}

etk::font_rendering::FontAtlas* etk::font_rendering::FontBook::GetAtlas(std::string fontName, etk::PointUnit pt, std::string fontPath)
{
	auto found = mFontAtlases.find(fontName + std::to_string(pt.GetPt(0, 0, 0, 0)));
	if (found != mFontAtlases.end()) {
		return found->second;
	}
	else {
		auto atlas = new FontAtlas(1024, 1024, fontPath, pt);
		mFontAtlases.insert(std::pair<std::string, FontAtlas*>(fontName + std::to_string(pt.GetPt(0, 0, 0, 0)), atlas));
		return atlas;
	}
}
