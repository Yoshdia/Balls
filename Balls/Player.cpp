#include"DxLib.h"
#include "Player.h"
#include "Game.h"


Player::Player(VECTOR initPos)
{
	pos = initPos;
	//�v���C���[���f����int�^��3d���f����ǂݍ���
	playerModel = new int;
	*playerModel = NULL;
	*playerModel = MV1LoadModel("model/whiteBall.mqo");
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
	
}

void Player::Render()
{

	//�����Ƀv���C���[���f����`��
	MV1SetPosition(*playerModel, VGet(0, 0, 0));
	MV1DrawModel(*playerModel);
}
