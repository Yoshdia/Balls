#pragma once
#include "Scene.h"

//Play�V�[��
class Play :
	public Scene
{
private:
	//�v���C���[���f��
	int *playerModel;
public:
	Play();
	~Play();

	void Update();
	void Render();
	sceneName SceneChange(char* key);

};

