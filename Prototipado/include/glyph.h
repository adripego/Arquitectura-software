#ifndef UGINE_GLYPH_H
#define UGINE_GLYPH_H

#include "image.h"

class Glyph {
public:
    Glyph();
    ~Glyph();
    void setStart(int32 x, int32 y);
    void setEnd(int32 x, int32 y);
    int32 getStartX();
    int32 getStartY();
    int32 getEndX();
    int32 getEndY();
private:
    int32 sX;
    int32 sY;
    int32 eX;
    int32 eY;
};

#endif