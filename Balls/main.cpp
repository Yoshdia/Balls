#include "DxLib.h"
#include"Game.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game* game;
	game = new Game();
	game->MainProcess();
	delete game;

	return 0;				// ソフトの終了 
}


