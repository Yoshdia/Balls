#include "DxLib.h"
#include"Game.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game* game;
	game = new Game();
	game->MainProcess();
	delete game;

	return 0;				// �\�t�g�̏I�� 
}


