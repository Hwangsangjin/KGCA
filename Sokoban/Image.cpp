#include "Image.h"
#include "File.h"

#include "GameLib/Framework.h"

using namespace GameLib;

Image::Image(const char* filename)
    : _width(0)
    , _height(0)
    , _data(nullptr)
{
    File f(filename);
    _height = f.GetUnsigned(12);
    _width = f.GetUnsigned(16);
    _data = new unsigned int[_width * _height];

    for (size_t i = 0; i < _width * _height; i++)
    {
        _data[i] = f.GetUnsigned(128 + i * 4);
    }
}

Image::~Image()
{
    delete[] _data;
    _data = nullptr;
}

int Image::GetWidth() const
{
    return _width;
}

int Image::GetHeight() const
{
    return _height;
}

void Image::Draw(int destX, int destY, int srcX, int srcY, int width, int height) const
{
    unsigned int* vram = Framework::instance().videoMemory();
    unsigned int windowWidth = Framework::instance().width();

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            unsigned src = _data[(y + srcY) * _width + (x + srcX)];
            unsigned* dst = &vram[(y + destY) * windowWidth + (x + destX)];
            unsigned srcA = (src & 0xff000000) >> 24;
            unsigned srcR = src & 0xff0000;
            unsigned srcG = src & 0x00ff00;
            unsigned srcB = src & 0x0000ff;
            unsigned dstR = *dst & 0xff0000;
            unsigned dstG = *dst & 0x00ff00;
            unsigned dstB = *dst & 0x0000ff;
            unsigned r = (srcR - dstR) * srcA / 255 + dstR;
            unsigned g = (srcG - dstG) * srcA / 255 + dstG;
            unsigned b = (srcB - dstB) * srcA / 255 + dstB;
            *dst = (r & 0xff0000) | (g & 0x00ff00) | b;
        }
    }
}
