#pragma once
#include "Scene.h"

//Play�V�[��
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

