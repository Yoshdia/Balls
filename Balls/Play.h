#pragma once
#include "Scene.h"

class Player;

//PlayÉVÅ[Éì
class Play :
	public Scene
{
private:
	Player *player;
	const VECTOR playerPos=VGet(0,0,0);
public:
	Play();
	~Play();

	void Update();
	void Render();
	sceneName SceneChange();

};

