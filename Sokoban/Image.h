#pragma once

class Image
{
private:
	int _width;
	int _height;
	unsigned int* _data;

public:
	Image(const char* filename);
	~Image();

	int GetWidth() const;
	int GetHeight() const;
	void Draw(int destX, int destY, int srcX, int srcY, int width, int height) const;
};

