#pragma once
#include "Scene.h"

class Player;

//Play�V�[��
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
};

