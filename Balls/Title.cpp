#include"DxLib.h"
#include "InputKey.h"
#include "Title.h"

Title::Title(DeepestSpawner* deepestSpawner, Player* pLeftPlayer,Player* pRightPlayer, Score* score):
	Scene(deepestSpawner, pLeftPlayer, pRightPlayer, score)
{
	leftPlayer->SetFirstPosition();
	rightPlayer->SetFirstPosition();
	titleImg = new int;
	*titleImg = LoadGraph("Resouce/img/Title.png", TRUE);
	enterImg = new int;
	*enterImg= LoadGraph("Resouce/img/Press.png", TRUE);
}

Title::~Title()
{
	delete titleImg;
	delete enterImg;
}

void Title::Update(float deltaTime)
{
	leftPlayer->MoveFirstPosition( deltaTime);
	rightPlayer->MoveFirstPosition(deltaTime);
}

void Title::Render()
{
	DrawFormatString(0,0,GetColor(255,255,255),"Title");
	DrawRotaGraph(Game::ScreenWidth / 2, 300, 1.0f, 0, *titleImg, TRUE);
	DrawRotaGraph(Game::ScreenWidth / 2, 500, 1.0f, 0, *enterImg, TRUE);
}

sceneName Title::SceneChange()
{
	if (InputKey::GetInstance()->GetAllInputKey()[KEY_INPUT_RETURN] == 1)
	{
		leftPlayer->SkipMoveFirstPosition();
		rightPlayer->SkipMoveFirstPosition();
		deepestSpawner->ReStartDeepestObject();
		return sceneName::play;
	}
	return sceneName::noChange;
}
