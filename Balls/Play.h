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
	Play();
	~Play();

	void Update();
	void Render();
	sceneName SceneChange();

private :
	int count;
	const int SpawnTime=100;
	WallSpawner *wallSpawner;
};

