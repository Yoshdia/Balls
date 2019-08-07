#pragma once
#include "Scene.h"

//ClearƒV[ƒ“
class Clear :
	public Scene
{
public:
	Clear(DeepestSpawner* deepestSpawner, Score* score);
	~Clear();

	void Update(float deltaTime);
	void Render();
	sceneName SceneChange();
};

