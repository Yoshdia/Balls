#include "Player.h"
#include <math.h>
#include "ModelComponent.h"
//#include "Game.h"

Player::Player(VECTOR initPos, Game::MoveDirection next, char moveKey, int model, int texture)
{
	pos = initPos;
	moveInThisKey = moveKey;
	nextMoveDirection = next;

	//playerModel��3d���f����ǂݍ���
	duplicateModel = new int;
	*duplicateModel = NULL;
	*duplicateModel = MV1DuplicateModel(model);

	//���f�����k��
	float scale = 0.1f;
	MV1SetScale(*duplicateModel, VGet(scale, scale, scale));
	//���f���Ƀe�N�X�`���𒣂�t����
	MV1SetTextureGraphHandle(*duplicateModel, 0, texture, FALSE);

	//�ړ��\��n�_�ƈړ����鋗���̏�����
	targetPos = pos.x;
	moveDistance = 0;

	rotate = VGet(-1,0,0);

	ModelComponent * sc;
	sc = new ModelComponent(this);
	Game::GetInstance()->AddModel(sc);

	int id = Game::GetInstance()->GetTexture("model/whiteBall.mqo");
	sc->SetModel(id);
}


Player::~Player()
{
	MV1DeleteModel(*duplicateModel);
	delete duplicateModel;
	duplicateModel = NULL;
}

void Player::Move()
{
	//�ړ����łȂ��ꍇ�̂ݓ��͂��󂯕t����
	if (pos.x == targetPos)
	{
		//�������Ɏ󂯎�����L�[�����͂��ꂽ�Ƃ�
		if (Game::GetInstance()->GetAllInputKey()[moveInThisKey] == 1)
		{
			//�ړ��\��n
			targetPos = pos.x + (MovingDistance*nextMoveDirection);
			//1F�ňړ����鋗��
			moveDistance = (((pos.x + nextMoveDirection) - pos.x) / MovingDistance);
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
		pos.x += moveDistance;
	}
}

void Player::UpdateActor(float deltaTime)
{
	//��]������
	rotate = VAdd(rotate, VGet(0.1f, 0, 0));
}

void Player::Render()
{
	//pos�ɕ`��
	//MV1SetPosition(*duplicateModel, pos);
	//MV1SetRotationXYZ(*duplicateModel, rotate);
	//MV1DrawModel(*duplicateModel);
}