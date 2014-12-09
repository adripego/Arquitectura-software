#include "../include/font.h"
#include "../include/renderer.h"
#include "../include/glyph.h"

extern "C"
{
    unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
    void stbi_image_free(void *buffer);
}

Font::~Font()
{

}

Font::Font(const String& filename) : Image(filename, 16, 16)
{ 
    unsigned char *buffer;
    int comp;
    int width, height;
    Glyph* glyph;
    

    buffer = stbi_load(filename.ToCString(), &width, &height, &comp, 4);   
    int frameX = width / 16;
    int frameY = height / 16;
    if (buffer)
    {
        for (unsigned int i = 0; i < height; i++)
        {
            for (unsigned int j = 0; j < width; j++)
            {
                for (unsigned int  k = 0; i < frameY; i++)
                {
                    for (unsigned int  l = 0; l < frameX; l++)
                    {
                        int index = (i + k) * (width + j + l) * 4;
                        glyph = new Glyph();

                        if (buffer[index] == 255 && buffer[index + 1] == 255 && buffer[index + 2] == 0)
                        {
                            buffer[index + 3] = 0;
                            glyph->setStart(k,l);
                        }
                        else if (buffer[index] == 255 && buffer[index + 1] == 0 && buffer[index + 2] == 0)
                        {
                            buffer[index + 3] = 0;
                            glyph->setEnd(k, l);
                        }
                        else if (buffer[index] == 0 && buffer[index] == 0 && buffer[index] == 0)
                        {
                            buffer[index + 3] = 255;
                        }
                        arrayGlyphs.Add(glyph);
                    }
                }
                j += frameX;
            }
            i += frameY;
        }
        stbi_image_free(buffer);
    }
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
    if (arrayGlyphs.Size() != 0)
    {
        double offsetX = 0.0;
        uint32 anchoCaracter;
        for (int32 i = 0; i < text.Length(); i++){
            uint16 eX = arrayGlyphs[text[i]]->getStartX();
            uint16 oY = arrayGlyphs[text[i]]->getStartY();
            Renderer::Instance().DrawImage(this, x + offsetX, y + oY, text[i]);
            anchoCaracter = this->GetWidth() - (this->GetWidth() - eX);
            offsetX += anchoCaracter;
        }
       
    }
    else
    {
        int charOffset = 0;
        int charWidth = this->GetSize();
        for (unsigned int i = 0; i < text.Length(); i++)
        {
            Renderer::Instance().DrawImage(this, charOffset + x, y, text[i]);
            charOffset += charWidth;
        }
    }
}