#include"DxLib.h"
#include "Play.h"
#include "Collider.h"
#include "Wall.h"
#include "InputKey.h"
#include "GameSpeedManager.h"


Play::Play(DeepestSpawner* deepestSpawner, Score* score):
	Scene(deepestSpawner,score)
{
	count = 0;
	gameEnd = false;
}


Play::~Play()
{
}

void Play::Update(float deltaTime)
{
	deepestSpawner->SpawnerUpdate(deltaTime);
	gameEnd = Collider::GetInstance()->CollisionCall();
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
	if (InputKey::GetInstance()->GetAllInputKey()[KEY_INPUT_0] == 1||gameEnd)
	{
		//gameSpeedのリセット
		GameSpeedManager::GetInstance()->ResetGameSpeed();
		//全てのWallを停止させる
		deepestSpawner->StopDeepestObject();
		return sceneName::clear;
	}
	return sceneName::noChange;
}
