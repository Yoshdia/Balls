#include"DxLib.h"
#include "Clear.h"
#include "InputKey.h"



Clear::Clear(DeepestSpawner* deepestSpawner, Player* pLeftPlayer,Player* pRightPlayer, Score* score):
	Scene(deepestSpawner,pLeftPlayer,pRightPlayer,score)
{
}


Clear::~Clear()
{
}

void Clear::Update(float deltaTime)
{
}

void Clear::Render()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Clear");
}

sceneName Clear::SceneChange()
{
	if (InputKey::GetInstance()->GetAllInputKey()[KEY_INPUT_0] == 1)
	{
		//‘S‚Ä‚Ì•Ç‚ðƒNƒŠƒA‚·‚é
		deepestSpawner->ClearDeepestObject();
		return sceneName::title;
	}
	return sceneName::noChange;
}

