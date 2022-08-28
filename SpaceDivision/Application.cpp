#include "pch.h"
#include "Application.h"
#include "GameCore.h"

int main()
{
	GameCore& game = *GameCore::Instance();
	game.Run();

	return 0;
}