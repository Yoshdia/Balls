#include "Player.h"
#include <math.h>
#include "ModelComponent.h"
//#include "Game.h"

Player::Player(VECTOR initPos, Game::MoveDirection next, char moveKey)
{
	position = initPos;
	moveInThisKey = moveKey;
	nextMoveDirection = next;

	//�ړ��\��n�_�ƈړ����鋗���̏�����
	targetPos = position.x;
	moveDistance = 0;

	//���f����ۑ����`�悷��Component������
	ModelComponent * modelComponent;
	modelComponent = new ModelComponent(this);
	int modelId = Game::GetInstance()->LoadModel("model/whiteBall.mqo","model/grade.JPG");
	modelComponent->SetModel(modelId);
	scale = 0.1f;
	modelComponent->SetModelScale(scale);
}


Player::~Player()
{
}

void Player::Move()
{
	//�ړ����łȂ��ꍇ�̂ݓ��͂��󂯕t����
	if (position.x == targetPos)
	{
		//�������Ɏ󂯎�����L�[�����͂��ꂽ�Ƃ�
		if (Game::GetInstance()->GetAllInputKey()[moveInThisKey] == 1)
		{
			//�ړ��\��n
			targetPos = position.x + (MovingDistance*nextMoveDirection);
			//1F�ňړ����鋗��
			moveDistance = (((position.x + nextMoveDirection) - position.x) / MovingDistance);
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
		position.x += moveDistance;
	}
}

void Player::UpdateActor(float deltaTime)
{
	//��]������
	rotation = VAdd(rotation, VGet(0.1f, 0, 0));
}
