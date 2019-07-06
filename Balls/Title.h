#pragma once
#include "Scene.h"

//タイトルシーン
class Title :
	public Scene
{
public:
	Title(WallSpawner* wallSpawn);
	~Title();

	void Update();
	void Render();
	sceneName SceneChange();
};

