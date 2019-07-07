//#include <iostream>
#include "DxLib.h"
#include "Scene.h"
#include "Player.h"
#include "Title.h"
#include "Play.h"
#include "Clear.h"
#include "Wall.h"
#include "Actor.h"
#include "ModelComponent.h"
#include "Ground.h"
#include "SphereColliderComponent.h"
#include "BoxColliderComponent.h"
#include "MoveComponent.h"
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib") 

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
	//キー情報の取得と初期化
	key = new char[ControlKeyNum];
	UpdateKey();

	wallSpawner = new WallSpawner;
	//最初のシーンを作成
	scene = new Play(wallSpawner);

	//カメラの視野範囲を設定
	SetCameraNearFar(nearCameraPos, farCameraPos);
	//カメラの場所を設定
	SetCameraPositionAndTarget_UpVecY(CameraPos, VGet(0, 0, 0));

	//ライトの向きをカメラから0,0,0を見るように設定

	SetLightDirection(VGet(0, -1, 2));
	//int secondLight = CreateDirLightHandle(VGet(1,-1,2));
	//int thirdLight = CreateDirLightHandle(VGet(-1, -1, 2));

	new Player(leftPlayerPos, Game::MoveDirection::Left, KEY_INPUT_SPACE);
	new Player(rightPlayerPos, Game::MoveDirection::Right, KEY_INPUT_RETURN);

	new Ground(VGet(0, -2.0f, 0));

	DWORD nowTick, prevTick;
	prevTick = timeGetTime();
	deltaTime = 1.0f;
	gameSpeed = 1.0f;

	//画面更新時にエラーが起きた時か、Escapeキーが押されたら終了
	while (ScreenUpdate() && key[KEY_INPUT_ESCAPE] == 0)
	{
		DeltaTimeSet(nowTick, prevTick);
		UpdateKey();

		ActorUpdate();
		scene->Update();

		DrawModel();
		scene->Render();

		SceneChange();
	}

	delete[] key;
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

bool Game::ScreenUpdate()
{
	if (ProcessMessage() != 0) return false;
	//画面の裏ページの内容を表ページに反映する
	if (ScreenFlip() != 0) return false;
	//画面を初期化
	if (ClearDrawScreen() != 0) return false;
	return true;
}

void Game::UpdateKey()
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


void Game::AddActor(Actor * actor)
{
	pendingActors.emplace_back(actor);
}

void Game::RemoveActor(Actor * actor)
{
	//actorをupDateingActorsとpendingActorsの中から削除する
	auto iter = std::find(pendingActors.begin(), pendingActors.end(), actor);
	if (iter != pendingActors.end())
	{
		std::iter_swap(iter, pendingActors.end() - 1);
		pendingActors.pop_back();
	}
	iter = std::find(upDateActors.begin(), upDateActors.end(), actor);
	if (iter != upDateActors.end())
	{
		std::iter_swap(iter, upDateActors.end() - 1);
		upDateActors.pop_back();
	}
}

void Game::ActorUpdate()
{
	//全てのActorの更新処理
	for (auto actor : upDateActors)
	{
		actor->Update(deltaTime);
	}
	//このF中で更新すべきActorの処理が全て終わった後にactorに挿入する
	for (auto actor : pendingActors)
	{
		upDateActors.emplace_back(actor);
	}
	pendingActors.clear();

	//全てのActorの中からStateがNoActiveのActorをdeleteActorsに移し削除する
	std::vector<Actor *> deleteActors;
	for (auto actor : upDateActors)
	{
		if (actor->GetState() == Actor::ActiveState::NoActive)
		{
			deleteActors.emplace_back(actor);
		}
	}
	//すべてのアクターをdeleteする
	for (auto actor : deleteActors)
	{
		delete actor;
	}
}

void Game::ShowActor()
{
	//printf("\n\n<-----------------Actor List---------------->\n");
	//printf("--------> Active Actor(%4d) <----------\n", mActors.size());
	//for (auto i : mActors)
	//{
	//	printf("mem[%p] : id %d ", i, i->GetID());
	//	std::cout << typeid(*i).name() << "\n";
	//}
	//printf("\n--------> Pending Actor(%4d) <----------\n", mPendingActors.size());
	//for (auto i : mPendingActors)
	//{
	//	printf("mem[%p] : id %d ", i, i->GetID());
	//	std::cout << typeid(*i).name() << "\n";
	//}
}

void Game::ShutDown()
{
	//upDateActorsの削除
	while (!upDateActors.empty())
	{
		delete upDateActors.back();
	}
	upDateActors.clear();

	//pendingActorsの削除
	while (!pendingActors.empty())
	{
		delete pendingActors.back();
	}
	pendingActors.clear();

	//model関連の解放
	for (auto model : originalModel)
	{
		MV1DeleteModel(model);
	}
	originalModel.clear();
	for (auto model : duplicateModel)
	{
		MV1DeleteModel(model.second);
	}
	duplicateModel.clear();
	for (auto model : modelTexture)
	{
		DeleteGraph(model.second);
	}
	modelTexture.clear();

	DxLib::DxLib_End();
}

int Game::LoadModel(const std::string & fileName, const std::string & textureFileName)
{
	/*fileNameのモデルを既に読み込んでいないか
	真の場合dupricateModel内のそのモデルアドレスを返し、
	偽の場合新たに読み込んでモデルアドレスを格納する*/
	int modelId;
	auto iter = duplicateModel.find(fileName);
	if (iter != duplicateModel.end())
	{
		modelId = iter->second;
	}
	else
	{
		int originalModelId = MV1LoadModel(fileName.c_str());
		originalModel.push_back(originalModelId);

		modelId = MV1DuplicateModel(originalModelId);
		duplicateModel.emplace(fileName.c_str(), modelId);

	}
	//テクスチャでも同じことをし最後にmodelIdにtextureIdを張り付ける
	int textureId;
	auto textureIter = modelTexture.find(textureFileName);
	if (textureIter != modelTexture.end())
	{
		textureId = textureIter->second;
	}
	else
	{
		textureId = LoadGraph(textureFileName.c_str());
		modelTexture.emplace(textureFileName.c_str(), textureId);
	}
	MV1SetTextureGraphHandle(modelId, 0, textureId, FALSE);

	return modelId;
}

void Game::AddModel(ModelComponent * model)
{
	//そのModelの更新順序を取得し、その順序より大きい値を見つけたらその前に挿入する
	int drawNumber = model->getProccesNumber();
	auto iter = modelComponents.begin();
	for (; iter != modelComponents.end(); ++iter)
	{
		int iterDrawNumber = (*iter)->getProccesNumber();
		if (drawNumber < iterDrawNumber ||
			drawNumber == iterDrawNumber)
		{
			break;
		}
	}
	modelComponents.insert(iter, model);
}

void Game::RemoveModel(ModelComponent * model)
{
	auto iter = std::find(modelComponents.begin(), modelComponents.end(), model);
	if (iter != modelComponents.end())
	{
		modelComponents.erase(iter);
	}
}

void Game::DrawModel()
{
	for (auto model : modelComponents)
	{
		model->DrawModel();
	}
}

void Game::AddBoxCollider(BoxColliderComponent * box)
{
	boxCollider.emplace_back(box);
}

void Game::RemoveCollider(BoxColliderComponent * box)
{
	auto iter = std::find(boxCollider.begin(), boxCollider.end(), box);
	if (iter != boxCollider.end())
	{
		std::iter_swap(iter, boxCollider.end() - 1);
		boxCollider.pop_back();
	}
}

void Game::AddSphereCollider(SphereColliderComponent * sphere)
{
	sphereCollider.emplace_back(sphere);
}

void Game::RemoveSphereCollider(SphereColliderComponent * sphere)
{
	auto iter = std::find(sphereCollider.begin(), sphereCollider.end(), sphere);
	if (iter != sphereCollider.end())
	{
		std::iter_swap(iter, sphereCollider.end() - 1);
		sphereCollider.pop_back();
	}
}

bool Game::CollisionCall()
{
	for (auto ball : sphereCollider)
	{
		for (auto box : boxCollider)
		{
			//壁の衝突準備フラグが立っていない場合ここで終了する
			if (!box->GetIsCollision())
			{
				continue;
			}
			bool end = CollisionBallWall(ball, box);
			if (end)
			{
				//加速壁だった場合、gameSpeedを加速させる
				if (box->GetTag() == BoxColliderComponent::ColliderTag::AddSpeedWall)
				{
					box->OnCollision();
					ball->OnCollision();
					
					continue;
				}
				//Playerが強化状態だった場合、壁をPauseにする
				if (ball->GetTag() == SphereColliderComponent::CollisionTag::SuperPlayer)
				{
					box->OnCollision();
					continue;
				}
				return end;
			}
		}
	}
	return false;
}

bool Game::CollisionBallWall(SphereColliderComponent * ball, BoxColliderComponent * wall)
{
	SphereInfo sphere = ball->GetInfo();
	BoxInfo box = wall->GetIndo();

	float sphereLengh = sphere.length*sphere.length;
	sphereLengh = 1;
	box.length = 1;


	if (box.position.x == sphere.position.x)
	{
		return true;
	}

	VECTOR boxLeftUp = VGet(box.position.x - box.length, box.position.y + box.length, 0);

	if (((boxLeftUp.x - sphere.position.x)*(boxLeftUp.x - sphere.position.x)) +
		((boxLeftUp.y - sphere.position.y)*(boxLeftUp.y - sphere.position.y)) <= sphereLengh)
	{
		return true;
	}

	VECTOR boxRightDown = VGet(box.position.x + box.length, box.position.y - box.length, 0);
	{
		if (((boxRightDown.x - sphere.position.x)*(boxRightDown.x - sphere.position.x)) +
			((boxRightDown.y - sphere.position.y)*(boxRightDown.y - sphere.position.y)) <= sphereLengh)
		{
			return true;
		}
	}
	return false;
}
