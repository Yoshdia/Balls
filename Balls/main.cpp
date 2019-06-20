#include "DxLib.h"
#include"main.h"

bool ScreenUpdate();

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetGraphMode(ScreenWidth, ScreenHeight, 32);

	SetDrawScreen(DX_SCREEN_BACK);

	while (ScreenUpdate()&&!CheckHitKey(KEY_INPUT_ESCAPE))
	{

	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

bool ScreenUpdate()
{
	if (ProcessMessage() != 0) return false;
	//画面の裏ページの内容を表ページに反映する
	if (ScreenFlip() != 0) return false;
	//画面を初期化
	if (ClearDrawScreen() != 0) return false;
	return true;
}