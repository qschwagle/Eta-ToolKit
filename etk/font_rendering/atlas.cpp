#include "atlas.h"

#include "ft2build.h"

#include FT_FREETYPE_H  

#include<string>

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

etk::font_rendering::FontAtlas::FontAtlas(int width, int height, std::string fontPath, DimensionalUnit pt) :
    mWidth{ width },
    mHeight{ height },
    mPt {pt},
    mAtlas{ static_cast<unsigned char*>(calloc(sizeof(unsigned char), width*height)) },
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
    if(error) {
        throw std::exception("Error occurred trying to initialize FT_Library");
    }
    error = FT_Set_Char_Size(mFreeFont->mFace, 0, mPt.GetPt(0,0,0,0) * 64, mHorizontalDensity, mVerticalDensity);
}

etk::font_rendering::FontAtlas::~FontAtlas()
{
    FT_Done_Face(mFreeFont->mFace);
    delete mFreeFont->mLibrary;
    delete mAtlas;
    delete mFreeFont;
}

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

    mCharacterHeight = slot->bitmap.rows;

    if (slot->bitmap.width + mPositionX < mWidth) {
    }
    else {
        mPositionX = 0;
        mPositionY += mCharacterHeight;
    }

    for (int i = 0; i < slot->bitmap.rows; i++) {
        std::copy(slot->bitmap.buffer + static_cast<size_t>(i)*slot->bitmap.width, slot->bitmap.buffer + (static_cast<size_t>(i)+1)*slot->bitmap.width, &mAtlas[mPositionX+mPositionY*mWidth+i*mWidth]);
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
    //mWidth += slot->bitmap.width + slot->advance.x >> 6;

    //if (mHeight < slot->bitmap.rows) {
    //    mHeight = slot->bitmap.rows;
    //}
    //if (mShift < (slot->bitmap.rows - slot->bitmap_top)) {
    //    mShift = (slot->bitmap.rows - slot->bitmap_top);
    //}
    mMap.insert({ character, std::move(glyph) });
    return mMap[character].get();
}
