#include"DxLib.h"
#include "Player.h"
#include "Game.h"


Player::Player(VECTOR initPos)
{
	pos = initPos;
	//プレイヤーモデルにint型の3dモデルを読み込む
	playerModel = new int;
	*playerModel = NULL;
	*playerModel = MV1LoadModel("model/whiteBall.mqo");
}


Player::~Player()
{
	//解放
	MV1DeleteModel(*playerModel);
	delete playerModel;
	playerModel = NULL;
}

void Player::Update()
{
	
}

void Player::Render()
{

	//中央にプレイヤーモデルを描画
	MV1SetPosition(*playerModel, VGet(0, 0, 0));
	MV1DrawModel(*playerModel);
}
