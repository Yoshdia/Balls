#include "Player.h"
#include <math.h>
#include "Game.h"

Player::Player(VECTOR initPos, PlayerMoveDirection next, char moveKey)
{
	pos = initPos;
	moveInThisKey = moveKey;
	nextMoveDirection = next;

	//playerModelに3dモデルを読み込む
	*model = MV1LoadModel("model/whiteBall.mqo");
	*duplicateModel = MV1DuplicateModel(*model);
	*modelTexture = LoadGraph("model/grade.JPG");

	//モデルを縮小
	float scale = 0.1f;
	MV1SetScale(*duplicateModel, VGet(scale, scale, scale));
	//モデルにテクスチャを張り付ける
	MV1SetTextureGraphHandle(*duplicateModel, 0,*modelTexture, FALSE);

	//移動予定地点と移動する距離の初期化
	targetPos = pos.x;
	moveDistance = 0;

	rotate = VGet(-1,0,0);
}


Player::~Player()
{
}

void Player::Update()
{
	//回転させる
	rotate=VAdd(rotate, VGet(0.1f, 0, 0));
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
	MV1SetPosition(*duplicateModel, pos);
	MV1SetRotationXYZ(*duplicateModel, rotate);
	MV1DrawModel(*duplicateModel);
}