#include "DxLib.h"
#include "InputKey.h"
#include "ActorManager.h"
#include "Renderer.h"
#include "Collider.h"

#include "Scene.h"
#include "Player.h"
#include "Title.h"
#include "Play.h"
#include "Clear.h"

#include "Ground.h"
#include "WallSpawner.h"
//DeltaTimeの計測に必要
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib") 

void Game::MainProcess()
{
	//Dxlib初期化処理
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

	wallSpawner = new WallSpawner;
	//最初のシーンを作成
	scene = new Play(wallSpawner);

	//カメラの視野範囲を設定
	SetCameraNearFar(nearCameraPos, farCameraPos);
	//カメラの場所を設定
	SetCameraPositionAndTarget_UpVecY(CameraPos, VGet(0, 0, 0));
	//ライトの向きを設定
	SetLightDirection(VGet(0, -1, 2));
	//int secondLight = CreateDirLightHandle(VGet(1,-1,2));
	//int thirdLight = CreateDirLightHandle(VGet(-1, -1, 2));

	new Player(leftPlayerPos, Game::MoveDirection::Left, KEY_INPUT_SPACE);
	new Player(rightPlayerPos, Game::MoveDirection::Right, KEY_INPUT_RETURN);
	new Ground(VGet(0, -2.0f, 0));

	//deltaTimeの計測
	DWORD nowTick, prevTick;
	prevTick = timeGetTime();

	gameSpeed = 1.0f;

	//画面更新時にエラーが起きた時か、Escapeキーが押されたら終了
	while (ScreenUpdate() && InputKey::GetInstance()->GetAllInputKey()[KEY_INPUT_ESCAPE] == 0)
	{
		DeltaTimeSet(nowTick, prevTick);
		InputKey::GetInstance()->UpdateKey();
		ActorManager::GetInstance()->ActorUpdate(deltaTime);

		scene->Update(deltaTime);

		Renderer::GetInstance()->DrawModel();
		scene->Render();

		SceneChange();
	}

	delete wallSpawner;
	wallSpawner = nullptr;
	delete scene;
	scene = nullptr;

	ShutDown();
	DeleteLightHandleAll();
	//Dxlibの終了
	DxLib_End();

	return;
}

void Game::CreateSingleTons()
{
	InputKey::GetInstance()->Create();
	ActorManager::GetInstance()->Create();
	Renderer::GetInstance()->Create();
	Collider::GetInstance()->Create();
}

void Game::DeleteSingleTons()
{
	ActorManager::GetInstance()->ShutDown();
	ActorManager::Delete();
	Renderer::GetInstance()->ShutDown();
	Renderer::GetInstance()->Delete();
	Collider::GetInstance()->ShutDown();
	Collider::GetInstance()->Delete();
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

void Game::SceneChange()
{
	sceneName nextScene = scene->SceneChange();
	switch (nextScene)
	{
	case(sceneName::title):
		delete scene;
		scene = new Title(wallSpawner);
		break;
	case(sceneName::play):
		delete scene;
		scene = new Play(wallSpawner);
		gameSpeed = 1.0f;
		break;
	case(sceneName::clear):
		scene = new Clear(wallSpawner);
		break;
	}
}

void Game::DeltaTimeSet(DWORD& nowTick, DWORD& prevTick)
{
	nowTick = timeGetTime();
	DWORD mTicks = DWORD(nowTick - prevTick);
	prevTick = timeGetTime();

	deltaTime = mTicks / 1000.0f;
	prevTick = nowTick;

	if (deltaTime >= 0.07f)
	{
		deltaTime = 0.07f;
	}
}

void Game::ShutDown()
{
	DeleteSingleTons();
	DxLib::DxLib_End();
}

VECTOR operator*(const VECTOR vec, const float flo)
{
	VECTOR vector;
	vector = VGet(vec.x*flo, vec.y*flo, vec.z*flo);
	return vector;
}

