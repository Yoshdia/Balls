#include "DxLib.h"
#include "Game.h"

Game *Game::game = NULL;

void Game::Create()
{
	if (!game)
	{
		game = new Game;
	}
}

void Game::Delete()
{
	delete game;
	game = NULL;
}

bool Game::ScreenUpdate()
{
	if (ProcessMessage() != 0) return false;
	//画面の裏ページの内容を表ページに反映する
	if (ScreenFlip() != 0) return false;
	//画面を初期化
	if (ClearDrawScreen() != 0) return false;
	return true;
}

void Game::SetUpdateKey(char * control)
{
	//現在の入力状態をtmpKeyにコピー
	char tmpKey[256];

	//全ての入力状態をtmpKeyに格納
	GetHitKeyStateAll(tmpKey);

	//num番目のキーが押されていたら加算
	for (int num = 0; num < ControlKeyNum; num++)
	{
		if (tmpKey[num] != 0)
		{
			control[num]++;
		}
		else
		{
			//押されていないキーは0にする
			control[num] = 0;
		}
	}
}

void Game::Update()
{
	//dxlib期化処理
	if (DxLib_Init() == -1)		
	{
		return;
	}
	//スクリーンモードの変更。true=ウィンドウモード
	ChangeWindowMode(true);
	//画面モードの変更
	SetGraphMode(ScreenWidth, ScreenHeight, 32);
	//描画先グラフィック領域を裏に
	SetDrawScreen(DX_SCREEN_BACK);
	//キー情報の取得と初期化
	char* key=new char[ControlKeyNum];
	SetUpdateKey(key);

	//画面更新時にエラーが起きた時か、Escapeキーが押されたら終了
	while (ScreenUpdate() && key[KEY_INPUT_ESCAPE]==0)
	{
		SetUpdateKey(key);
	}

	delete[] key;

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return;
}
