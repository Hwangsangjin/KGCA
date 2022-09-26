#include "GameLib/Framework.h"

namespace GameLib
{
	void Framework::update()
	{
		unsigned int* vram = videoMemory();
		vram[200 * width() + 100] = 0xff0000;
	}
}