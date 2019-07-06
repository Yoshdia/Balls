#pragma once
#include "Scene.h"
class WallSpawner;
class Player;

//PlayÉVÅ[Éì
class Play :
	public Scene
{
private:

public:
	Play(WallSpawner* wallSpawn);
	~Play();

	void Update();
	void Render();
	sceneName SceneChange();

private :
	int count;
	const int SpawnTime=100;
	bool gameEnd;
};

