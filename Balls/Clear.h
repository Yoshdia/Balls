#pragma once
#include "Scene.h"

//Clear�V�[��
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

