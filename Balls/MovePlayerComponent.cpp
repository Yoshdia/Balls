#include "DxLib.h"
#include "Game.h"
#include "MovePlayerComponent.h"
#include "Actor.h"

MovePlayerComponent::MovePlayerComponent(Actor * owner, int processNumber, char moveKey, Game::MoveDirection next)
	:MoveComponent(owner, processNumber, VGet(0, 0, 0))
	, nextMoveDirection(next)
	, targetPos(owner->GetPosition().x)
	, moveInputeKey(moveKey)
	, moving(false)
	,movement(MovingDistance)
	,middlePos((float)2*next)
{
}

MovePlayerComponent::~MovePlayerComponent()
{
}

void MovePlayerComponent::Update(float deltaTime)
{
	//�ړ����łȂ��ꍇ�̂ݓ��͂��󂯕t����
	if (!moving)
	{
		//�C���X�^���X�������Ɏ󂯎����moveInputKey�����͂��ꂽ�Ƃ�
		if (Game::GetInstance()->GetAllInputKey()[moveInputeKey] == 1)
		{
			//�ړ��\��n�̌v�Z
			targetPos = middlePos + (MovingDistance/2*nextMoveDirection);
			//�c��ړ�����
			movement = targetPos-position.x;
			//1f�Ɉړ����鋗��
			moveDistance.x = movement * movingRequiredTime;
			//�c��ړ��������Βl�ɕϊ�
			movement = abs(movement);
			//�E�Ɉړ����Ă����ꍇ���Ɂ@�̂悤�ɍ��E�؂�ւ�����悤�ɂ���
			switch (nextMoveDirection)
			{
			case(Game::MoveDirection::Right):nextMoveDirection = Game::MoveDirection::Left; break;
			case(Game::MoveDirection::Left):nextMoveDirection = Game::MoveDirection::Right; break;
			}
			moving = true;
		}
	}
	else
	{
		Move(deltaTime);
		//�c��ړ�������0�ɂȂ�܂ňړ��𑱂���
		movement -= (moveDistance.x*deltaTime)*-nextMoveDirection;
		if (movement<=0)
		{
			position.x = targetPos;
			ownerActor->SetPosition(position);
			moving = false;
		}
	}
}
