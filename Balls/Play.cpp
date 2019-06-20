#include"DxLib.h"
#include "Play.h"
#include "Game.h"

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
	//3D‹óŠÔ‚Ì”FŽ¯‚ÆƒJƒƒ‰‚Ì³í“®ì‚Ì‚½‚ß‚É’†‰›‚É10Žž‚Ìü‚ð•`‚­
	DrawLine3D(VGet(-5, 0, 0), VGet(5, 0, 0), GetColor(255, 255, 255));
	DrawLine3D(VGet(0, -5, 0), VGet(0, 5, 0), GetColor(255, 255, 255));
	
}

sceneName Play::SceneChange()
{
	if (Game::GetInstance()->GetAllInputKey()[KEY_INPUT_0] == 1)
	{
		return sceneName::clear;
	}
	return sceneName::noChange;
}
