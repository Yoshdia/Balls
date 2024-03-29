#pragma once

class Scene;
class Camera;
#include"DxLib.h"

class BoxColliderComponent;
class SphereColliderComponent;
class DeepestSpawner;
class Score;
class Player;

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

	//スクリーンサイズ
	static const int ScreenWidth ;
	static const int ScreenHeight;

private:
	Scene *scene;

	Camera* camera;

	//Dxlib関数にあるそれぞれの設定を行う関数
	void DxlibWindowSetting();
	void DxlibCameraSetting();
	void DxlibLightSetting();

	//シングルトンクラスの生成と解放
	void CreateSingleTons();
	void DeleteSingleTons();

	//最初に登場するActor達を生成する関数
	void CreateFirstActors();

	//画面の更新。エラーが起きた場合ゲームを終了する
	bool ScreenUpdate();

	//シーンチェンジ。Sceneの派生クラスから条件と遷移先を決める
	void SceneChange();
	//時間計測
	void DeltaTimeSet(DWORD &nowTick, DWORD &prevTick);



	//カメラの座標
	static const VECTOR CameraPos;
	static const VECTOR LightPos;

	//プレイヤーの初期座標
	const VECTOR leftPlayerPos = VGet(-1, 0, 0);
	const VECTOR rightPlayerPos = VGet(1, 0, 0);

	DeepestSpawner* deepestSpawner;
	 Score* score;
	 Player* leftPlayer;
	 Player* rightPlayer;

	//時間
	float deltaTime;
};

//VECTORとfloatの乗算結果を返す
VECTOR operator*(const VECTOR& vec, const float& flo);
VECTOR operator*(const VECTOR& vec, const VECTOR& multi);