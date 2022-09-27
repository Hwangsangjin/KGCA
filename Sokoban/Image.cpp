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
    _width = f.GetUnsigned(16);
    _height = f.GetUnsigned(12);
    _data = new unsigned[_width * _height];

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
            unsigned int* dest = &vram[(y + destY) * windowWidth + (x + destX)];
            *dest = _data[(y + srcY) * _width + (x + srcX)];
        }
    }
}
