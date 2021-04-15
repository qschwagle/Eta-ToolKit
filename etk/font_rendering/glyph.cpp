#include "glyph.h"

#include "atlas.h"

/// <summary>
/// Loads the provided vector with the vertices and increases the x by glyph Advance
/// </summary>
/// <param name="begin">vertices vector</param>
/// <param name="x">used for positioning x direction and increased</param>
void etk::font_rendering::FontGlyph::LoadVertices(std::vector<float>::iterator& begin, float& x) noexcept
{
    const float y = 0;
    const float xW = x + GetWidth();
    const float yH = y + GetBearingY();
    *begin = x;
    begin += 1;
    *begin = yH;
    begin += 1;
    *begin = mAtlasX / static_cast<float>(mAtlas->GetWidth());
    begin += 1;
    *begin = mAtlasY / static_cast<float>(mAtlas->GetHeight());
    begin += 1;

    *begin = x;
    begin += 1;
    *begin = y;
    begin += 1;
    *begin = mAtlasX / static_cast<float>(mAtlas->GetWidth());
    begin += 1;
    *begin = (mAtlasY + mHeight) / static_cast<float>(mAtlas->GetHeight());
    begin += 1;

    *begin = xW;
    begin += 1;
    *begin = y;
    begin += 1;
    *begin = (mAtlasX + mWidth) / static_cast<float>(mAtlas->GetWidth());
    begin += 1;
    *begin = (mAtlasY + mHeight) / static_cast<float>(mAtlas->GetHeight());
    begin += 1;

    *begin = x;
    begin += 1;
    *begin = yH;
    begin += 1;
    *begin = mAtlasX / static_cast<float>(mAtlas->GetWidth());
    begin += 1;
    *begin = mAtlasY / static_cast<float>(mAtlas->GetHeight());
    begin += 1;

    *begin = xW;
    begin += 1;
    *begin = y;
    begin += 1;
    *begin = (mAtlasX + mWidth) / static_cast<float>(mAtlas->GetWidth());
    begin += 1;
    *begin = (mAtlasY + mHeight) / static_cast<float>(mAtlas->GetHeight());
    begin += 1;

    *begin = xW;
    begin += 1;
    *begin = yH;
    begin += 1;
    *begin = (mAtlasX + mWidth) / static_cast<float>(mAtlas->GetWidth());
    begin += 1;
    *begin = mAtlasY / static_cast<float>(mAtlas->GetHeight());
    begin += 1;

    x += mAdvance;
}