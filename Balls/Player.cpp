#include"DxLib.h"
#include "Player.h"
#include <math.h>
#include "Game.h"

Player::Player(VECTOR initPos, PlayerMoveDirection next, char moveKey)
{
	pos = initPos;
	moveInThisKey = moveKey;
	nextMoveDirection = next;

	//playerModelに3dモデルを読み込む
	playerModel = new int;
	*playerModel = NULL;
	*playerModel = MV1LoadModel("model/whiteBall.mqo");

	//モデルを縮小
	float scale = 0.1f;
	MV1SetScale(*playerModel, VGet(scale, scale, scale));

	//移動予定地点と移動する距離の初期化
	targetPos = pos.x;
	moveDistance = 0;
}


Player::~Player()
{
	//playerModelの解放
	MV1DeleteModel(*playerModel);
	delete playerModel;
	playerModel = NULL;
}

void Player::Update()
{
	Move();
}

void Player::Move()
{
	//移動中でない場合のみ入力を受け付ける
	if (pos.x == targetPos)
	{
		//生成時に受け取ったキーが入力されたとき
		if (Game::GetInstance()->GetAllInputKey()[moveInThisKey] == 1)
		{
			//移動予定地
			targetPos = pos.x + (MovingDistance*nextMoveDirection);
			//1Fで移動する距離
			moveDistance = (((pos.x + nextMoveDirection) - pos.x) / MovingDistance);
			//右に移動していた場合左に　のように左右切り替えられるようにする
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
	//posに描画
	MV1SetPosition(*playerModel, pos);
	MV1DrawModel(*playerModel);
}
