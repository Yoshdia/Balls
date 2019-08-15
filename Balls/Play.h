#pragma once
#include "Scene.h"
class Player;

//PlayÉVÅ[Éì
class Play :
	public Scene
{
private:

public:
	Play(DeepestSpawner* deepestSpawner, Player* pLeftPlayer,Player* pRightPlayer, Score* score);
	~Play();

	void Update(float deltaTime);
	void Render();
	sceneName SceneChange();

private :
	int count;
	const int SpawnTime=100;
	bool gameEnd;
	bool ending;
	int endCount;
};

