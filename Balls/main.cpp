#include "DxLib.h"
#include"Game.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game::GetInstance()->Create();
	Game::GetInstance()->Update();
	Game::GetInstance()->Delete();

	return 0;				// �\�t�g�̏I�� 
}


