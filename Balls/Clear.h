#pragma once
#include "Scene.h"

//ClearÉVÅ[Éì
class Clear :
	public Scene
{
public:
	Clear(DeepestSpawner* deepestSpawner,Player* pLeftPlayer,Player* pRightPlayer, Score* score);
	~Clear();

	void Update(float deltaTime);
	void Render();
	sceneName SceneChange();
};

