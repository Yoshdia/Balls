#pragma once
#include "Scene.h"

//�^�C�g���V�[��
class Title :
	public Scene
{
public:
	Title(DeepestSpawner* deepestSpawner, Player* pLeftPlayer,Player* pRightPlayer, Score* score);
	~Title();

	void Update(float deltaTime);
	void Render();
	sceneName SceneChange();
};

