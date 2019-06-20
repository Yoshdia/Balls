#pragma once
#include "Scene.h"

//ClearƒV[ƒ“
class Clear :
	public Scene
{
public:
	Clear();
	~Clear();

	void Update();
	void Render();
	sceneName SceneChange(char* key);
};

