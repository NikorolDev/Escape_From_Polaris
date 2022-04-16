#ifdef _DEBUG
#include <iostream>
//#include <vld.h>
#endif

#include "GameLoader.h"

int main()
{
	//Create an istance of game loader and initialise the game
	GameLoader gameLoader;
	gameLoader.initialise();

	return 0;
}