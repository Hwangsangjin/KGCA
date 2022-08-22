#include "Collision.h"

bool Collision::RectToInRect(Rect& a, Rect& b)
{
	if (a._left <= b._left && (a._left + a._right) >= (b._left + b._right)
		&&
		a._top <= b._top && (a._top + a._bottom) >= (b._top + b._bottom))
	{
		return true;
	}

    return false;
}
