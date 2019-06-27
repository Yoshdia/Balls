#include "DxLib.h"
#include "Game.h"
#include "MovePlayerComponent.h"

MovePlayerComponent::MovePlayerComponent(Actor * owner, int processNumber, char moveKey, Game::MoveDirection next)
	:MoveComponent(owner,processNumber,VGet(0,0,0))
	,nextMoveDirection(next)
	,targetPos(position.x)
	,moveInputeKey(moveKey)
{
}

MovePlayerComponent::~MovePlayerComponent()
{
}

void MovePlayerComponent::Update(float deltaTime)
{
	//�ړ����łȂ��ꍇ�̂ݓ��͂��󂯕t����
	if (position.x == targetPos)
	{
		//�������Ɏ󂯎�����L�[�����͂��ꂽ�Ƃ�
		if (Game::GetInstance()->GetAllInputKey()[moveInputeKey] == 1)
		{
			//�ړ��\��n
			targetPos = position.x + (MovingDistance*nextMoveDirection);
			//1F�ňړ����鋗��
			moveDistance.x = (((position.x + nextMoveDirection) - position.x) / MovingDistance);
			//�E�Ɉړ����Ă����ꍇ���Ɂ@�̂悤�ɍ��E�؂�ւ�����悤�ɂ���
			switch (nextMoveDirection)
			{
			case(Game::MoveDirection::Right):nextMoveDirection = Game::MoveDirection::Left; break;
			case(Game::MoveDirection::Left):nextMoveDirection = Game::MoveDirection::Right; break;
			}
		}
	}
	else
	{
		Move(deltaTime);
	}
}
