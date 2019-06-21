#include "Player.h"
#include <math.h>
#include "Game.h"

Player::Player(VECTOR initPos, PlayerMoveDirection next, char moveKey)
{
	pos = initPos;
	moveInThisKey = moveKey;
	nextMoveDirection = next;

	//playerModel��3d���f����ǂݍ���
	*model = MV1LoadModel("model/whiteBall.mqo");
	*duplicateModel = MV1DuplicateModel(*model);
	*modelTexture = LoadGraph("model/grade.JPG");

	//���f�����k��
	float scale = 0.1f;
	MV1SetScale(*duplicateModel, VGet(scale, scale, scale));
	//���f���Ƀe�N�X�`���𒣂�t����
	MV1SetTextureGraphHandle(*duplicateModel, 0,*modelTexture, FALSE);

	//�ړ��\��n�_�ƈړ����鋗���̏�����
	targetPos = pos.x;
	moveDistance = 0;

	rotate = VGet(-1,0,0);
}


Player::~Player()
{
}

void Player::Update()
{
	//��]������
	rotate=VAdd(rotate, VGet(0.1f, 0, 0));
	Move();
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
			case(RightMove):nextMoveDirection = LeftMove; break;
			case(LeftMove):nextMoveDirection = RightMove; break;
			}
		}
	}
	else
	{
		pos.x += moveDistance;
	}
}

void Player::Render()
{
	//pos�ɕ`��
	MV1SetPosition(*duplicateModel, pos);
	MV1SetRotationXYZ(*duplicateModel, rotate);
	MV1DrawModel(*duplicateModel);
}