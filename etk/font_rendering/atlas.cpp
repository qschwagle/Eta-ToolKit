#include "atlas.h"

#include "ft2build.h"

#include FT_FREETYPE_H  

#include<string>

/// <summary>
/// Container for Freefont data structures
/// </summary>
struct etk::font_rendering::FreeFont 
{
	/// <summary>
	/// freetype library
	/// </summary>
	FT_Library* mLibrary;

	/// <summary>
	/// Freetype face
	/// </summary>
	FT_Face mFace;
};

/// <summary>
/// Constructor 
/// 
/// Creates the Texture atlas and initializes FreeFont with a font and font size
/// </summary>
/// <param name="width">pixel width of atlas</param>
/// <param name="height">pixel height of atlas</param>
/// <param name="fontPath">font used for rendering</param>
/// <param name="pt">font size</param>
etk::font_rendering::FontAtlas::FontAtlas(int width, int height, std::string fontPath, DimensionalUnit pt) :
    mWidth{ width },
    mHeight{ height },
    mPt {pt},
    mAtlas{ static_cast<unsigned char*>(calloc(sizeof(unsigned char), width*static_cast<long>(height))) },
    mFreeFont { new FreeFont }
{
    mFreeFont->mLibrary = new FT_Library;

    int error = FT_Init_FreeType(mFreeFont->mLibrary);
    if(error) {
        throw std::exception("Error occurred trying to initialize FT_Library");
    }

	error = FT_New_Face(*mFreeFont->mLibrary, fontPath.c_str(), 0, &mFreeFont->mFace);
    if (error == FT_Err_Unknown_File_Format) {
        throw std::exception("Error occurred trying to initializing Face: unknown file format");
    }
    else if (error) {
        const char* error_message = FT_Error_String(error);
        if (!error_message) {
            auto message = std::string("Error occurred trying to initializing Face: ") + std::to_string(error);
            throw std::exception(message.c_str());
        }
        else {
            auto message = std::string("Error occurred trying to initializing Face: ") + std::string(FT_Error_String(error));
            throw std::exception(message.c_str());
        }
    }

    error = FT_Set_Char_Size(mFreeFont->mFace, 0, mPt.GetPt(0,0,0,0) * 64, mHorizontalDensity, mVerticalDensity);
    if(error) {
        throw std::exception("Error occurred trying to initialize FT_Library");
    }
}

/// <summary>
/// Deconstructor
/// 
/// Cleans up Freefont and the atlas
/// </summary>
etk::font_rendering::FontAtlas::~FontAtlas()
{
    FT_Done_Face(mFreeFont->mFace);
    delete mFreeFont->mLibrary;
    free(mAtlas);
    delete mFreeFont;
}

/// <summary>
/// Retrieves and caches glyphs into the texture atlas
/// </summary>
/// <param name="character">character whose glyph is being retrieved</param>
/// <returns>glyph</returns>
etk::font_rendering::FontGlyph* etk::font_rendering::FontAtlas::GetGlyph(unsigned int character)
{
    auto found = mMap.find(character);
    if (found != mMap.end()) {
        return found->second.get();
    }

    int error = FT_Load_Char(mFreeFont->mFace, character, FT_LOAD_RENDER);
    if (error) throw std::exception("etk::font_rendering::FontRendering::SetCharacter::FT_Load_Char Error");

    auto glyph = std::make_unique<FontGlyph>();
    FT_GlyphSlot slot = mFreeFont->mFace->glyph;
    FT_UInt glyph_index;

    auto characterHeight = slot->bitmap.rows;

    if (slot->bitmap.width + mPositionX >= mWidth) {
        mPositionX = 0;
        mPositionY += characterHeight + 5;
    }

    // copy the bitmap to the texture atlas
    for (size_t i = 0; i < slot->bitmap.rows; i++) {
        std::copy(
            slot->bitmap.buffer + i * slot->bitmap.width, 
            slot->bitmap.buffer + (i + 1) * slot->bitmap.width, 
            mAtlas+(mPositionX + mPositionY * mWidth+i*mWidth)
        );
    }

    glyph->SetGlyph(
        slot->bitmap.width,
        slot->bitmap.rows,
        mPositionX,
        mPositionY,
        this,
        slot->bitmap_left,
        slot->bitmap_top,
        slot->advance.x >> 6
    );

    mPositionX += slot->bitmap.width;

    mMap.insert({ character, std::move(glyph) });

    return mMap[character].get();
}
