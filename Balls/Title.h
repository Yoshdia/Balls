#pragma once
#include "Scene.h"

//�^�C�g���V�[��
class Title :
	public Scene
{
public:
	Title();
	~Title();

	void Update();
	void Render();
	sceneName SceneChange();
};

