#include"DxLib.h"
#include "Player.h"
#include "Game.h"


void Player::Move()
{
}

Player::Player(VECTOR initPos)
{
	pos = initPos;
	//�v���C���[���f����int�^��3d���f����ǂݍ���
	playerModel = new int;
	*playerModel = NULL;
	*playerModel = MV1LoadModel("model/whiteBall.mqo");

	pos = VGet(0, 0, 0);
	targetPos = pos.x;
	needDis = 0;
}


Player::~Player()
{
	//���
	MV1DeleteModel(*playerModel);
	delete playerModel;
	playerModel = NULL;
}

void Player::Update()
{
	if (Game::GetInstance()->GetAllInputKey()[KEY_INPUT_RETURN]==1)
	{
		 targetPos = pos.x + MovingDistance;
	     needDis = MovingDistance / movingRequiredTime;

	}
	if (Game::GetInstance()->GetAllInputKey()[KEY_INPUT_SPACE] == 1)
	{
		targetPos = pos.x - MovingDistance;
		needDis = -MovingDistance / movingRequiredTime;
	}
	if ((int)pos.x != (int)targetPos)
	{
		pos.x += needDis;
	}
	else
	{
		targetPos = pos.x;
		needDis = 0;
	}
}

void Player::Render()
{

	//�����Ƀv���C���[���f����`��
	MV1SetPosition(*playerModel,pos);
	MV1DrawModel(*playerModel);
}
