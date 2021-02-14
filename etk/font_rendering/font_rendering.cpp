#include "font_rendering.h"


#include <iostream>


#include <locale>
#include <codecvt>

etk::font_rendering::FontRendering::FontRendering(std::wstring fontPath)
{
    mLibrary = new FT_Library;
    int error = FT_Init_FreeType(mLibrary);
    if(error) {
        std::cout << "QSLabel::Init Error occurred trying to initialize FT_Library" << std::endl;
        exit(1);
    }
    setlocale(LC_ALL, "");
    auto converter = std::wstring_convert<std::codecvt_utf8<wchar_t>>();
    std::string mbs = converter.to_bytes(fontPath);
	error = FT_New_Face(*mLibrary, mbs.c_str(), 0, &mFace);
    if (error == FT_Err_Unknown_File_Format) {
        std::cout << "QSLabel::Init Error occurred trying to initializing Face: unknown file format" << std::endl;
        exit(1);
    }
    else if (error) {
        const char* error_message = FT_Error_String(error);
        if (!error_message) {
            std::cout << "QSLabel::Init Error occurred trying to initializing Face: " << error << std::endl;
        }
        else {
            std::cout << "QSLabel::Init Error occurred trying to initializing Face: " << FT_Error_String(error) << std::endl;
        }
        exit(1);
    }
    if(error) {
       std::cout << "QSLabel::Init Error occurred trying to initialize FT_Library" << std::endl;
       exit(1);
    }
    error = FT_Set_Char_Size(mFace, 0, mPtHeight * 64, mHor, mVert);
}

etk::font_rendering::FontRendering::~FontRendering()
{
    FT_Done_Face(mFace);
    delete mLibrary;
}

void etk::font_rendering::FontRendering::SetDpi(float hor, float vert) {
	mHor = hor;
	mVert = vert;
    int error = FT_Set_Char_Size(mFace, 0, mPtHeight * 64, mHor, mVert);
}

void etk::font_rendering::FontRendering::SetPt(unsigned int pt) {
	mPtHeight = pt;
    int error = FT_Set_Char_Size(mFace, 0, mPtHeight * 64, mHor, mVert);
}


void etk::font_rendering::FontRendering::SetCharacter(std::weak_ptr<etk::renderer::Character> character, unsigned int c)
{
    auto characterLock = character.lock();
    FT_GlyphSlot slot = mFace->glyph;
    FT_UInt glyph_index;

    int error = FT_Load_Char(mFace, c, FT_LOAD_RENDER);
    if (error) throw std::exception("etk::font_rendering::FontRendering::SetCharacter::FT_Load_Char Error");
    characterLock->LoadGlyph(
        slot->advance.x >> 6, 
        slot->bitmap.width, 
        slot->bitmap.rows, 
        slot->bitmap_left, 
        slot->bitmap_top, 
        slot->bitmap.buffer
    );
    mWidth += slot->bitmap.width + slot->advance.x >> 6;

    if (mHeight < slot->bitmap.rows) {
        mHeight = slot->bitmap.rows;
    }
    if (mShift < (slot->bitmap.rows - slot->bitmap_top)) {
        mShift = (slot->bitmap.rows - slot->bitmap_top);
    }
}
