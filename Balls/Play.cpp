#include"DxLib.h"
#include "Play.h"

Play::Play()
{
}


Play::~Play()
{
}

void Play::Update()
{
}

void Play::Render()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Play");
}

sceneName Play::SceneChange(char* key)
{
	if (key[KEY_INPUT_0] == 1)
	{
		return sceneName::clear;
	}
	return sceneName::noChange;
}
