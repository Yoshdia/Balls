#include"DxLib.h"
#include "Game.h"
#include "Title.h"

Title::Title()
{
}

Title::~Title()
{
}

void Title::Update()
{
	
}

void Title::Render()
{
	DrawFormatString(0,0,GetColor(255,255,255),"Title");
}

sceneName Title::SceneChange(char* key)
{
	if (key[KEY_INPUT_0] == 1)
	{
		return sceneName::play;
	}
	return sceneName::noChange;
}
