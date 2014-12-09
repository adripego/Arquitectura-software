#ifndef UGINE_FONT_H
#define UGINE_FONT_H

#include "image.h"
#include "glyph.h"

class Font : public Image {
public:
    Font(const String& filename);
    ~Font();
    virtual uint16 GetSize() const;
    virtual uint32 GetTextWidth(const String& text) const;
    virtual uint32 GetTextHeight(const String& text) const;
    virtual void Render(const String& text, double x, double y);
private:
    Array <Glyph*> arrayGlyphs;
};

#endif