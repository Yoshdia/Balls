#include"DxLib.h"
#include "Play.h"
#include "Player.h"

Play::Play()
{
	player = new Player(playerPos);
}


Play::~Play()
{
	delete player;
}

void Play::Update()
{
	player->Update();
}

void Play::Render()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Play");
	//3D‹óŠÔ‚Ì”FŽ¯‚ÆƒJƒƒ‰‚Ì³í“®ì‚Ì‚½‚ß‚É’†‰›‚É10Žž‚Ìü‚ð•`‚­
	DrawLine3D(VGet(-5, 0, 0), VGet(5, 0, 0), GetColor(255, 255, 255));
	DrawLine3D(VGet(0, -5, 0), VGet(0, 5, 0), GetColor(255, 255, 255));
	player->Render();
}

sceneName Play::SceneChange(char* key)
{
	if (key[KEY_INPUT_0] == 1)
	{
		return sceneName::clear;
	}
	return sceneName::noChange;
}
