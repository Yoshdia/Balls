#include "DxLib.h"
#include"Game.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game::GetInstance()->Create();
	Game::GetInstance()->Update();
	Game::GetInstance()->Delete();

	return 0;				// ソフトの終了 
}


