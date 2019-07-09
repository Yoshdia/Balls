#include"DxLib.h"
#include "Play.h"
#include "Game.h"
#include "Wall.h"
#include "WallSpawner.h"


Play::Play(WallSpawner* wallSpawn):
	Scene(wallSpawn)
{
	count = 0;
	gameEnd = false;
}


Play::~Play()
{
}

void Play::Update(float deltaTime)
{
	wallSpawner->WallSpawn(deltaTime);
	gameEnd = Game::GetInstance()->CollisionCall();
	if (gameEnd)
	{
		wallSpawner->WallStop();
	}
}

void Play::Render()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Play");
	//3D空間の認識とカメラの正常動作のために中央に10時の線を描く
	//DrawLine3D(VGet(-5, 0, 0), VGet(5, 0, 0), GetColor(255, 255, 255));
	//DrawLine3D(VGet(0, -5, 0), VGet(0, 5, 0), GetColor(255, 255, 255));
}

sceneName Play::SceneChange()
{
	if (Game::GetInstance()->GetAllInputKey()[KEY_INPUT_0] == 1||gameEnd)
	{
		return sceneName::clear;
	}
	return sceneName::noChange;
}
