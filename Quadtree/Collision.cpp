#include "Collision.h"

bool Collision::RectToInRect(Rect& a, Rect& b)
{
	if (a.left <= b.left && (a.left + a.right) >= (b.left + b.right)
		&&
		a.top <= b.top && (a.top + a.bottom) >= (b.top + b.bottom))
	{
		return true;
	}

    return false;
}
