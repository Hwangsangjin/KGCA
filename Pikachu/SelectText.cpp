#include "pch.h"
#include "SelectText.h"

HRESULT SelectText::Frame()
{
	SetPosition(_position);

	return TRUE;
}
