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

	//WallSetter *wallSetter = new WallSetter;
	//wallSetter->SetWall();
	Wall *wall = new Wall;

	mDeltaTime = 0;

	//画面更新時にエラーが起きた時か、Escapeキーが押されたら終了
	while (ScreenUpdate() && key[KEY_INPUT_ESCAPE] == 0)
	{
		SetUpdateKey();

		ActorUpdate();
		scene->Update();

		wall->Update();
		//wallSetter->Update();

		scene->Render();
		leftPlayer->Render();
		rightPlayer->Render();
		wall->Render();
		Game::GetInstance()->DrawModel();
		//wallSetter->Render();
		DrawGraph(10,10,*playerModelTexture,TRUE);

		SceneChange();


	}
	 
	delete[] key;
	delete scene;
	//delete leftPlayer;
	//delete rightPlayer;
	delete wall;
	//delete wallSetter;

	MV1DeleteModel(*playerModel);
	delete playerModel;
	playerModel = NULL;
	DeleteGraph(*playerModelTexture);
	delete playerModelTexture;
	playerModelTexture = NULL;
	ShutDown();

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

void Game::AddActor(Actor * actor)
{
	mPendingActors.emplace_back(actor);
}

void Game::RemoveActor(Actor * actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}
	// それはアクティブアクター内にいる？
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::ActorUpdate()
{
	// すべてのアクターの更新処理
	for (auto actor : mActors)
	{
		actor->Update(mDeltaTime);
	}
	// ペンディング中アクター
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	//　すべてのアクター中から死んでいるアクターをdeadActorsに
	std::vector<Actor *>deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}
	//すべてのアクターをdeleteする
	for (auto actor : deadActors)
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
	//スプライトコンポーネントの削除


	//アクターの削除
	while (!mActors.empty())
	{
		delete mActors.back();
	}
	mActors.clear();

	//ペンディングアクターの削除
	while (!mPendingActors.empty())
	{
		delete mPendingActors.back();
	}
	mPendingActors.clear();

	DxLib::DxLib_End();
}

int Game::GetTexture(const std::string & fileName)
{
	int retID;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		retID = iter->second;
	}
	else
	{
		/*retID = LoadGraph(fileName.c_str());*/
		retID=MV1LoadModel(fileName.c_str());

		//モデルを縮小
		float scale = 0.1f;
		MV1SetScale(retID, VGet(scale, scale, scale));

		mTextures.emplace(fileName.c_str(), retID);
	}
	return retID;
}

void Game::AddModel(ModelComponent * model)
{
	//ソートされたベクトル内の挿入点を見つける
	//そのモデルが望んだ描画順番の通りに挿入してやる
	int myDrawOrder = model->GetDrawOrder();
	auto iter = mModels.begin();
	for (;
		iter != mModels.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	mModels.insert(iter, model);
}

void Game::RemoveModel(ModelComponent * model)
{
	auto iter = std::find(mModels.begin(), mModels.end(), model);
	if (iter != mModels.end())
	{
		mModels.erase(iter);
	}
}

void Game::DrawModel()
{
	for (auto model : mModels)
	{
		model->Draw();
	}
}

