#include"DxLib.h"
#include "Clear.h"
#include "Game.h"



Clear::Clear()
{
}


Clear::~Clear()
{
}

void Clear::Update()
{
}

void Clear::Render()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Clear");
}

sceneName Clear::SceneChange()
{
	if (Game::GetInstance()->GetAllInputKey()[KEY_INPUT_0] == 1)
	{
		return sceneName::title;
	}
	return sceneName::noChange;
}
