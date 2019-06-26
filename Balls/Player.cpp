#include "Player.h"
#include <math.h>
#include "ModelComponent.h"
//#include "Game.h"

Player::Player(VECTOR initPos, Game::MoveDirection next, char moveKey, int model, int texture)
{
	pos = initPos;
	moveInThisKey = moveKey;
	nextMoveDirection = next;

	//playerModelに3dモデルを読み込む
	duplicateModel = new int;
	*duplicateModel = NULL;
	*duplicateModel = MV1DuplicateModel(model);

	//モデルを縮小
	float scale = 0.1f;
	MV1SetScale(*duplicateModel, VGet(scale, scale, scale));
	//モデルにテクスチャを張り付ける
	MV1SetTextureGraphHandle(*duplicateModel, 0, texture, FALSE);

	//移動予定地点と移動する距離の初期化
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
	//回転させる
	rotate = VAdd(rotate, VGet(0.1f, 0, 0));
}

void Player::Render()
{
	//posに描画
	//MV1SetPosition(*duplicateModel, pos);
	//MV1SetRotationXYZ(*duplicateModel, rotate);
	//MV1DrawModel(*duplicateModel);
}