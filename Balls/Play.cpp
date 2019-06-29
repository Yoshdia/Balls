#include"DxLib.h"
#include "Play.h"
#include "Game.h"
#include "Wall.h"

Play::Play()
{
	count = 0;
}


Play::~Play()
{
}

void Play::Update()
{
	count++;
	if (count >= SpawnTime)
	{
		int rand = GetRand(1);
		VECTOR wallPos = VGet(1, 0, 30);
		
		wallPos.x += (rand * 2);
		new Wall(wallPos);
		
		rand = GetRand(1);
		wallPos = VGet(1, 0, 30);
		wallPos.x += (rand * 2);
		wallPos.x *= -1;
		new Wall(wallPos);
		count = 0;
	}
}

void Play::Render()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Play");
	//3D‹óŠÔ‚Ì”FŽ¯‚ÆƒJƒƒ‰‚Ì³í“®ì‚Ì‚½‚ß‚É’†‰›‚É10Žž‚Ìü‚ð•`‚­
	//DrawLine3D(VGet(-5, 0, 0), VGet(5, 0, 0), GetColor(255, 255, 255));
	//DrawLine3D(VGet(0, -5, 0), VGet(0, 5, 0), GetColor(255, 255, 255));
}

sceneName Play::SceneChange()
{
	if (Game::GetInstance()->GetAllInputKey()[KEY_INPUT_0] == 1)
	{
		return sceneName::clear;
	}
	return sceneName::noChange;
}
