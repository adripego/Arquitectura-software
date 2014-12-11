#include "../include/font.h"
#include "../include/renderer.h"


Font::Font(const String& filename) : Image(filename, 16, 16)
{

}

uint16 Font::GetSize() const
{
    return this->GetHeight();
}

uint32 Font::GetTextWidth(const String& text) const
{
    return this->GetHeight() * text.Length();
}

uint32 Font::GetTextHeight(const String& text) const
{
    return this->GetHeight();
}

void Font::Render(const String& text, double x, double y)
{
    int charOffset = 0;
    int charWidth = this->GetSize();
    for (int i = 0; i < text.Length(); i++)
    {
        Renderer::Instance().DrawImage(this, charOffset + x, y, text[i]);
        charOffset += charWidth;
    }
}

