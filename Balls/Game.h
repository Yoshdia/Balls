#pragma once

class Scene;
class Camera;
class Actor;
#include <vector>
#include"DxLib.h"
#include<unordered_map>

class ModelComponent;
class BoxColliderComponent;
class SphereColliderComponent;
class WallSpawner;

//ゲーム全体の処理
class Game
{
public:
	static Game *GetInstance() { return game; }

	//gameシングルトンの生成と解放関数
	static void Create();
	static void Delete();
	
	char* GetAllInputKey() { return key; };

	//全体の処理を行う関数
	void MainProcess();

	//オブジェクトがどちらの向きへ進むのかの列挙体。移動距離MovingDistanceに直接乗算する
	enum MoveDirection
	{
		Right = 1,
		Left = -1,
	};

	void AddActor(Actor *actor);
	void RemoveActor(Actor *actor);
	void ActorUpdate();
	void ShowActor();

	void ShutDown();

	//fileNameのモデルが既に読み込まれたかどうかを検索しそうでなかった場合読み込んでそのアドレスを返す
	int LoadModel(const std::string &fileName);
	void AddModel(ModelComponent* model);
	void RemoveModel(ModelComponent* model);
	void DrawModel();

	void AddBoxCollider(BoxColliderComponent* box);
	void RemoveCollider(BoxColliderComponent* box);
	void AddSphereCollider(SphereColliderComponent* sphere);
	void RemoveSphereCollider(SphereColliderComponent* sphere);
	//衝突判定を行う関数を呼ぶ関数。戻り値は同じ　Playから呼ばれる
	bool CollisionCall();
	float GetGameSpeed() { return gameSpeed; }
	void AddGameSpeed() { gameSpeed += PlusSpeed; }
private:
	Game() {};
	static Game *game;

	Scene *scene;

	char* key;

	//画面の更新。エラーが起きた場合ゲームを終了する
	bool ScreenUpdate();
	//全ての入力状態を取得
	void UpdateKey();
	//シーンチェンジ。Sceneの派生クラスから条件と遷移先を決める
	void SceneChange();
	//時間計測
	void DeltaTimeSet(DWORD &nowTick, DWORD &prevTick);

	const float PlusSpeed = 0.01f;;
	float gameSpeed;

	//スクリーンサイズ
	const int ScreenWidth = 1080;
	const int ScreenHeight = 900;
	//キーボードから取得できるキーの最大数
	const int ControlKeyNum = 256;
	//カメラの座標
	const VECTOR CameraPos = VGet(0, 5, -10);
	//カメラの視野範囲
	const float nearCameraPos = 1;
	const float farCameraPos = 1000;
	const VECTOR LightPos = CameraPos;//VGet(0,CameraPos.y*10,CameraPos.z*10);

	//プレイヤーの初期座標
	const VECTOR leftPlayerPos = VGet(-1, 0, 0);
	const VECTOR rightPlayerPos = VGet(1, 0, 0);
	
	//更新中のActor
	std::vector<class Actor*> upDateActors;
	//保留中のActor
	std::vector<class Actor*> pendingActors;
	//ModelComponent
	std::vector<class ModelComponent*>  modelComponents;//mModel 


	//modelへのアドレス(解放を最後に行うためのvector)
	std::vector<int> duplicateModel;
	//アドレスの複製
	std::unordered_map<std::string, int> originalModel;
	//球(Player)と壁(wall)を格納しているVector
	std::vector<SphereColliderComponent*> sphereCollider;
	std::vector<BoxColliderComponent*> boxCollider;
	//衝突判定を行うフレンド関数
	 bool CollisionBallWall(SphereColliderComponent * player, BoxColliderComponent * wall);

	 WallSpawner* wallSpawner;

	//時間
	float deltaTime;

};