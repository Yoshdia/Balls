#pragma once
#include "Scene.h"

//Playシーン
class Play :
	public Scene
{
private:
	//プレイヤーモデル
	int *playerModel;
public:
	Play();
	~Play();

	void Update();
	void Render();
	sceneName SceneChange(char* key);

};

