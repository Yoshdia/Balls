#pragma once

class Scene;
class Camera;

//ゲーム全体の処理
class Game
{
public:
	static Game *GetInstance() { return game; }

	//gameシングルトンの生成と解放関数
	static void Create();
	static void Delete();
	
	char* GetAllInputKey();

	//全体の処理を行う関数
	void Update();

private:
	Game() {};
	static Game *game;

	Scene *scene;

	char* key;

	//画面の更新。エラーが起きた場合ゲームを終了する
	bool ScreenUpdate();
	//全ての入力状態を取得
	void SetUpdateKey();
	//シーンチェンジ。Sceneの派生クラスから条件と遷移先を決める
	void SceneChange();

	//スクリーンサイズ
	const int ScreenWidth = 1080;
	const int ScreenHeight = 900;
	//キーボードから取得できるキーの最大数
	const int ControlKeyNum = 256;
	//カメラの座標
	const VECTOR CameraPos = VGet(0, 0, -10);
	//カメラの視野範囲
	const float nearCameraPos = 0;
	const float farCameraPos = 50.0f;

	//プレイヤーの初期座標
	const VECTOR leftPlayerPos = VGet(-1, 0, 0);
	const VECTOR rightPlayerPos = VGet(1, 0, 0);
};