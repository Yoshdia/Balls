#pragma once
#include "Scene.h"

class Player;

//PlayƒV[ƒ“
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

};

