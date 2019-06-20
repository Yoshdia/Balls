#pragma once

class Scene;

//ゲーム全体の処理
class Game
{
private:
	Game() {};
	static Game *game;
	Scene *scene;

	bool ScreenUpdate();
	void SetUpdateKey(char* control);
	void SceneChange(char* key);

	//スクリーンサイズ
	const int ScreenWidth = 500;
	const int ScreenHeight = 500;
	const int ControlKeyNum = 256;
public:
	static Game *GetInstance() { return game; }

	//gameシングルトンの生成と解放関数
	static void Create();
	static void Delete();
	
	//全体の処理を行う関数
	void Update();
};