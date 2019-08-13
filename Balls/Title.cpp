#include"DxLib.h"
#include "InputKey.h"
#include "Title.h"

Title::Title(DeepestSpawner* deepestSpawner, Player* pLeftPlayer,Player* pRightPlayer, Score* score):
	Scene(deepestSpawner, pLeftPlayer, pRightPlayer, score)
{
	leftPlayer->SetFirstPosition();
	rightPlayer->SetFirstPosition();
}

Title::~Title()
{
}

void Title::Update(float deltaTime)
{
	leftPlayer->MoveFirstPosition( deltaTime);
	rightPlayer->MoveFirstPosition(deltaTime);
}

void Title::Render()
{
	DrawFormatString(0,0,GetColor(255,255,255),"Title");
}

sceneName Title::SceneChange()
{
	if (InputKey::GetInstance()->GetAllInputKey()[KEY_INPUT_0] == 1)
	{
		leftPlayer->SkipMoveFirstPosition();
		rightPlayer->SkipMoveFirstPosition();
		deepestSpawner->ReStartDeepestObject();
		return sceneName::play;
	}
	return sceneName::noChange;
}
