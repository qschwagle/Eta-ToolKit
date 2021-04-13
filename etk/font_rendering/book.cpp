#include "book.h"

/// <summary>
/// Retrieves an atlas with the provided font and font size. It creates one with the given fontpath if not available.
/// </summary>
/// <param name="fontName">name of font</param>
/// <param name="pt">font size</param>
/// <param name="fontPath">path to font, used if not already loaded</param>
/// <returns>font atlas</returns>
etk::font_rendering::FontAtlas* etk::font_rendering::FontBook::GetAtlas(std::string fontName, etk::PointUnit pt, std::string fontPath)
{
	auto found = mFontAtlases.find(fontName + std::to_string(pt.GetPt(0, 0, 0, 0)));
	if (found != mFontAtlases.end()) {
		return found->second.get();
	}
	else {
		auto atlas = std::make_unique<FontAtlas>(4096, 4096, fontPath, pt);
		auto atlasPtr = atlas.get();
		mFontAtlases.insert(std::pair<std::string, std::unique_ptr<FontAtlas>>(fontName + std::to_string(pt.GetPt(0, 0, 0, 0)), std::move(atlas)));
		return atlasPtr;
	}
}
