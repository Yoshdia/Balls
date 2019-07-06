#pragma once
#include "Scene.h"

//ClearÉVÅ[Éì
class Clear :
	public Scene
{
public:
	Clear(WallSpawner* wallSpawn);
	~Clear();

	void Update();
	void Render();
	sceneName SceneChange();
};

