#ifndef _ETK_FONT_BOOK_H_
#define _ETK_FONT_BOOK_H_

#include<unordered_map>
#include<string>

#include "atlas.h"
#include "etk/style/dimensional_unit.h"

namespace etk {
namespace font_rendering {

/// <summary>
/// A FontBook is an object containing all font atlases
/// for the library. 
/// </summary>
class FontBook {
public:
	FontBook();
	FontBook(const FontBook&) = delete;
	FontBook(const FontBook&&) = delete;
	FontBook& operator=(const FontBook&) = delete;

	virtual ~FontBook();

	/// <summary>
	/// Retrieves the atlas for a given fontName. If the font is not loaded,
	/// it uses the fontPath to create a new atlas. If it cannot create a new atlas,
	/// it returns nullptr.
	/// </summary>
	/// <param name="fontName">name of font to be retrieved</param>
	/// <param name="fontPath">path to font if new font is created</param>
	/// <returns>FontAtlas if present or creatable, nullptr otherwise</returns>
	FontAtlas* GetAtlas(std::string fontName, etk::PointUnit pt, std::string fontPath="");

private:
	/// <summary>
	/// atlases mapping
	/// </summary>
	std::unordered_map<std::string, FontAtlas*> mFontAtlases;
};
}
}
#endif 