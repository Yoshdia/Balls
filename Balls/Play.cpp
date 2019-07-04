#include"DxLib.h"
#include "Play.h"
#include "Game.h"
#include "Wall.h"
#include "WallSpawner.h"


Play::Play()
{
	count = 0;
	wallSpawner = new WallSpawner;
}


Play::~Play()
{
	delete wallSpawner;
}

void Play::Update()
{
	wallSpawner->WallSpawn();
}

void Play::Render()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Play");
	//3D��Ԃ̔F���ƃJ�����̐��퓮��̂��߂ɒ�����10���̐���`��
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
