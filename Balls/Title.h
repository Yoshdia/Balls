#pragma once
#include "Scene.h"

//タイトルシーン
class Title :
	public Scene
{
public:
	Title(WallSpawner* wallSpawn);
	~Title();

	void Update(float deltaTime);
	void Render();
	sceneName SceneChange();
};

