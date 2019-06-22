#include "DxLib.h"
#include "Scene.h"
#include "Player.h"
#include "Title.h"
#include "Play.h"
#include "Clear.h"
#include "WallSetter.h"

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

char * Game::GetAllInputKey()
{
	return key;
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
	key = new char[ControlKeyNum];
	SetUpdateKey();

	//最初のシーンを作成
	scene = new Play;

	//カメラの視野範囲を設定
	SetCameraNearFar(nearCameraPos, farCameraPos);
	//カメラの場所を設定
	SetCameraPositionAndTarget_UpVecY(CameraPos, VGet(0, 0, 0));
	//ライトの場所をカメラと同じ位置に設定
	SetLightPosition(CameraPos);
	//ライトの向きをカメラから0,0,0を見るように設定
	SetLightDirection(VGet(0, 0, 1));

	int *playerModel;
	playerModel = new int;
	*playerModel=MV1LoadModel("model/whiteBall.mqo");
	int *playerModelTexture;
	playerModelTexture = new int;
	*playerModelTexture = NULL;
	*playerModelTexture = LoadGraph("model/grade.JPG");

	Player *leftPlayer = new Player(leftPlayerPos, Game::MoveDirection::Left,KEY_INPUT_SPACE,*playerModel, *playerModelTexture);
	Player *rightPlayer = new Player(rightPlayerPos, Game::MoveDirection::Right,KEY_INPUT_RETURN,*playerModel, *playerModelTexture);

	WallSetter *wallSetter = new WallSetter;

	wallSetter->SetWall();
	//画面更新時にエラーが起きた時か、Escapeキーが押されたら終了
	while (ScreenUpdate() && key[KEY_INPUT_ESCAPE] == 0)
	{
		SetUpdateKey();

		scene->Update();
		leftPlayer->Update();
		rightPlayer->Update();
		wallSetter->Update();

		scene->Render();
		leftPlayer->Render();
		rightPlayer->Render();
		wallSetter->Render();

		SceneChange();
	}

	delete[] key;
	delete scene;
	delete leftPlayer;
	delete rightPlayer;
	delete wallSetter;

	MV1DeleteModel(*playerModel);
	delete playerModel;
	playerModel = NULL;
	DeleteGraph(*playerModelTexture);
	delete playerModelTexture;
	playerModelTexture = NULL;

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return;
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

void Game::SetUpdateKey()
{

	//全ての入力状態をtmpKeyに格納
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);

	//num番目のキーが押されていたら加算
	for (int num = 0; num < ControlKeyNum; num++)
	{
		if (tmpKey[num] != 0)
		{
			key[num]++;
		}
		else
		{
			//押されていないキーは0にする
			key[num] = 0;
		}
	}
}

void Game::SceneChange()
{
	sceneName nextScene = scene->SceneChange();
	switch (nextScene)
	{
	case(sceneName::title):
		delete scene;
		scene = new Title;
		break;
	case(sceneName::play):
		delete scene;
		scene = new Play;
		break;
	case(sceneName::clear):
		scene = new Clear;
		break;
	}
}
