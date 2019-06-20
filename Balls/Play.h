#pragma once
#include "Scene.h"

//PlayƒV[ƒ“
class Play :
	public Scene
{
public:
	Play();
	~Play();

	void Update();
	void Render();
	sceneName SceneChange(char* key);
};

