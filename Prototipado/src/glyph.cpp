#include "../include/glyph.h"

Glyph::Glyph()
{

}

Glyph::~Glyph()
{

}

void Glyph::setStart(int32 x, int32 y)
{
    this->sX = x;
    this->sY = y;
}

void Glyph::setEnd(int32 x ,int32 y)
{
    this->eX = x;
    this->eY = y;
}

int32 Glyph::getStartX()
{
    return this->sX;
}

int32 Glyph::getStartY()
{
    return this->sY;
}

int32 Glyph::getEndX()
{
    return this->eX;
}

int32 Glyph::getEndY()
{
    return this->eY;
}

