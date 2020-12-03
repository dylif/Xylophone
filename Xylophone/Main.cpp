#include "Main.hpp"

#include <iostream>

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "Engine.hpp"

int main(void)
{
	Engine pgeApp;
	if (pgeApp.Construct(PGE_SCREEN_WIDTH, PGE_SCREEN_HEIGHT, PX_WIDTH, PX_HEIGHT))
		pgeApp.Start();

	return 0;
}