#pragma once
#include "Scene.h"

//タイトルシーン
class Title :
	public Scene
{
public:
	Title();
	~Title();

	void Update();
	void Render();
	sceneName SceneChange();
};

