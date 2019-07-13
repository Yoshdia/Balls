#pragma once

class Scene;
class Camera;
#include"DxLib.h"

class BoxColliderComponent;
class SphereColliderComponent;
class WallSpawner;

//ゲーム全体の処理
class Game
{
public:
	Game() {};

	//全体の処理を行う関数
	void MainProcess();

	//オブジェクトがどちらの向きへ進むのかの列挙体。移動距離MovingDistanceに直接乗算する
	enum MoveDirection
	{
		Right = 1,
		Left = -1,
	};

	void ShutDown();

	float GetGameSpeed() { return gameSpeed; }
	void AddGameSpeed() { gameSpeed += PlusSpeed; }
private:
	Scene *scene;

	//シングルトンクラスの生成と解放
	void CreateSingleTons();
	void DeleteSingleTons();

	//画面の更新。エラーが起きた場合ゲームを終了する
	bool ScreenUpdate();

	//シーンチェンジ。Sceneの派生クラスから条件と遷移先を決める
	void SceneChange();
	//時間計測
	void DeltaTimeSet(DWORD &nowTick, DWORD &prevTick);

	const float PlusSpeed = 0.01f;;
	float gameSpeed;

	//スクリーンサイズ
	const int ScreenWidth = 1080;
	const int ScreenHeight = 900;

	//カメラの座標
	const VECTOR CameraPos = VGet(0, 5, -10);
	//カメラの視野範囲
	const float nearCameraPos = 1;
	const float farCameraPos = 1000;
	const VECTOR LightPos = CameraPos;

	//プレイヤーの初期座標
	const VECTOR leftPlayerPos = VGet(-1, 0, 0);
	const VECTOR rightPlayerPos = VGet(1, 0, 0);

	 WallSpawner* wallSpawner;

	//時間
	float deltaTime;
};

//VECTORとfloatの乗算結果を返す
VECTOR operator*(const VECTOR vec, const float flo);