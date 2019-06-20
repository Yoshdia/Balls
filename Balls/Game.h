#pragma once

class Scene;
class Camera;

//ゲーム全体の処理
class Game
{
private:
	Game() {};
	static Game *game;

	Scene *scene;

	char* key;

	bool ScreenUpdate();
	void SetUpdateKey();
	void SceneChange();

	//スクリーンサイズ
	const int ScreenWidth = 1080;
	const int ScreenHeight = 900;
	const int ControlKeyNum = 256;
	const float nearCameraPos = 0;
	const float farCameraPos = 1000.0f;

	const VECTOR CameraPos = VGet(0, 0, -100);
public:
	static Game *GetInstance() { return game; }

	//gameシングルトンの生成と解放関数
	static void Create();
	static void Delete();
	
	char* GetAllInputKey();

	//全体の処理を行う関数
	void Update();
};