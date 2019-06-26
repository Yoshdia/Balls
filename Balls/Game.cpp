//#include <iostream>
#include "DxLib.h"
#include "Scene.h"
#include "Player.h"
#include "Title.h"
#include "Play.h"
#include "Clear.h"
#include "Wall.h"
#include "WallSetter.h"
#include "Actor.h"
#include"ModelComponent.h"


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

	int *playerModelTexture;
	playerModelTexture = new int;
	*playerModelTexture = NULL;
	*playerModelTexture = LoadGraph("model/grade.JPG");

	new Player(leftPlayerPos, Game::MoveDirection::Left,KEY_INPUT_SPACE, *playerModelTexture);
	new Player(rightPlayerPos, Game::MoveDirection::Right,KEY_INPUT_RETURN, *playerModelTexture);

	Wall *wall = new Wall;
	
	//DWORD nowTick, prevTick;
	//prevTick = timeGetTime();
	deltaTime = 1.0f;

	//画面更新時にエラーが起きた時か、Escapeキーが押されたら終了
	while (ScreenUpdate() && key[KEY_INPUT_ESCAPE] == 0)
	{
		//DeltaTimeSet(&nowTick,&prevTick);
		UpdateKey();

		ActorUpdate();
		scene->Update();

		wall->Update();

		Game::GetInstance()->DrawModel();
		wall->Render();
		scene->Render();

		SceneChange();
	}
	 
	delete[] key;
	delete scene;
	delete wall;

	DeleteGraph(*playerModelTexture);
	delete playerModelTexture;
	playerModelTexture = NULL;

	ShutDown();
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

void Game::DeltaTimeSet(DWORD * nowTick, DWORD * prevTick)
{
	//*nowTick = timeGetTime();
	//DWORD mTicks = DWORD(nowTick - prevTick);
	//*prevTick = timeGetTime();

	//deltaTime = mTicks / 1000.0f;
	//*prevTick = *nowTick;
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

	//modelsの削除
	for (auto model : models)
	{
		MV1DeleteModel(model.second);
	}
	models.clear();

	DxLib::DxLib_End();
}

int Game::LoadModel(const std::string & fileName)
{
	int modelId;
	auto iter = models.find(fileName);
	if (iter != models.end())
	{
		modelId = iter->second;
	}
	else
	{
		modelId =MV1LoadModel(fileName.c_str());
		models.emplace(fileName.c_str(), modelId);
	}
	return modelId;
}

void Game::AddModel(ModelComponent * model)
{
	//そのModelの更新順序を取得し、その順序より大きい値を見つけたらその前に挿入する
	int drawNumber = model->getProccesNumber();
	auto iter = modelComponents.begin();
	for (;iter != modelComponents.end();++iter)
	{
		int iterDrawNumber = (*iter)->getProccesNumber();
		if (drawNumber < iterDrawNumber||
			drawNumber== iterDrawNumber)
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

