#include"DxLib.h"
#include "Play.h"
#include "Collider.h"
#include "Wall.h"
#include "InputKey.h"
#include "GameSpeedManager.h"

Play::Play(DeepestSpawner* deepestSpawner, Player* pLeftPlayer, Player* pRightPlayer, Score* score) :
	Scene(deepestSpawner, pLeftPlayer, pRightPlayer, score),
	endCount(0)
{
	count = 0;
	gameEnd = false;
	leftPlayer->StartMove();
	rightPlayer->StartMove();
	score->ClearScore();
}


Play::~Play()
{
}

void Play::Update(float deltaTime)
{
	deepestSpawner->SpawnerUpdate(deltaTime);
	gameEnd = Collider::GetInstance()->CollisionCall(score);
	if (gameEnd)
	{
		endCount++;
	}
}

void Play::Render()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Play");
	int nowScore = score->GetScore();
	DrawFormatString(0, 16, GetColor(255, 255, 255), "Score:%d", nowScore);
	//3D��Ԃ̔F���ƃJ�����̐��퓮��̂��߂ɒ�����10���̐���`��
	//DrawLine3D(VGet(-5, 0, 0), VGet(5, 0, 0), GetColor(255, 255, 255));
	//DrawLine3D(VGet(0, -5, 0), VGet(0, 5, 0), GetColor(255, 255, 255));
}

sceneName Play::SceneChange()
{
	if (InputKey::GetInstance()->GetAllInputKey()[KEY_INPUT_0] == 1 || (gameEnd&&endCount>2))
	{
		leftPlayer->StopMove();
		rightPlayer->StopMove();
		//gameSpeed�̃��Z�b�g
		GameSpeedManager::GetInstance()->ResetGameSpeed();
		//�S�Ă�Wall���~������
		deepestSpawner->StopDeepestObject();
		return sceneName::clear;
	}
	return sceneName::noChange;
}
