#include "atlas.h"

etk::font_rendering::FontAtlas::FontAtlas(int width, int height, std::string fontPath, DimensionalUnit pt) :
    mWidth{ width },
    mHeight{ height },
    mAtlas{ new unsigned char[mWidth*mHeight] }
{
    mLibrary = new FT_Library;
    int error = FT_Init_FreeType(mLibrary);
    if(error) {
        throw std::exception("Error occurred trying to initialize FT_Library");
    }
	error = FT_New_Face(*mLibrary, fontPath.c_str(), 0, &mFace);
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
    error = FT_Set_Char_Size(mFace, 0, mPt.GetPt(0,0,0,0) * 64, mHorizontalDensity, mVerticalDensity);
}

etk::font_rendering::FontAtlas::~FontAtlas()
{
    FT_Done_Face(mFace);
    delete mLibrary;
    delete mAtlas;
}

etk::font_rendering::FontGlyph* etk::font_rendering::FontAtlas::GetGlyph(unsigned int character)
{
    FontGlyph* glyph = new FontGlyph;
    FT_GlyphSlot slot = mFace->glyph;
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

    int error = FT_Load_Char(mFace, character, FT_LOAD_RENDER);
    if (error) throw std::exception("etk::font_rendering::FontRendering::SetCharacter::FT_Load_Char Error");
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
    mWidth += slot->bitmap.width + slot->advance.x >> 6;

    //if (mHeight < slot->bitmap.rows) {
    //    mHeight = slot->bitmap.rows;
    //}
    //if (mShift < (slot->bitmap.rows - slot->bitmap_top)) {
    //    mShift = (slot->bitmap.rows - slot->bitmap_top);
    //}
    return glyph;
}
