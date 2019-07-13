#include "DxLib.h"
#include "InputKey.h"
#include "MovePlayerComponent.h"
#include "Actor.h"

const float MovePlayerComponent::MovingRequiredTime = 10.0f;
const float MovePlayerComponent::MovingDistanceSum = 2.0f;

MovePlayerComponent::MovePlayerComponent(Actor * owner, int processNumber, char moveKey, Game::MoveDirection next, VECTOR rotateSpeed)
	:MoveComponent(owner, processNumber, VGet(0, 0, 0),rotateSpeed)
	, nextMoveDirection(next)
	, targetPos(owner->GetPosition().x)
	, moveInputeKey(moveKey)
	, moving(false)
	,movement(MovingDistanceSum)
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
		if (InputKey::GetInstance()->GetAllInputKey()[moveInputeKey] == 1)
		{
			//�ړ��\��n�̌v�Z
			targetPos = middlePos + (MovingDistanceSum/2*nextMoveDirection);
			//�c��ړ�����
			movement = targetPos-position.x;
			//float gameSpeed = Game::GetInstance()->GetGameSpeed();
			float gameSpeed = 1.0f;
			//1f�Ɉړ����鋗��
			moveDistance.x = (movement * MovingRequiredTime)*deltaTime*gameSpeed;
			//MoveComponent����gameSpeed�����ȏ�܂ŏ㏸����ƈړ����������v�ړ����������邱�Ƃ����邽�ߏ���l��ݒ�
			if (moveDistance.x >= MovingDistanceSum)
			{
				moveDistance.x = MovingDistanceSum;
			}
			//�c��ړ��������Βl�ɕϊ�
			movement = abs(movement);
			//�ړ�������E�؂�ւ���
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
		//MoveComponent���́A�l���v�Z������֐���
		Move();
		//�c��ړ�������0�ɂȂ�܂ňړ��𑱂���
		movement -= moveDistance.x*-nextMoveDirection;
		if (movement<=0)
		{
			position.x = targetPos;
			ownerActor->SetPosition(position);
			moving = false;
		}
	}
	Rotate(deltaTime);
}
