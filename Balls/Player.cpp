#include "Player.h"
#include <math.h>
#include "ModelComponent.h"
//#include "Game.h"

Player::Player(VECTOR initPos, Game::MoveDirection next, char moveKey,int texture)
{
	position = initPos;
	moveInThisKey = moveKey;
	nextMoveDirection = next;

	//*duplicateModel = MV1DuplicateModel(model);

	//モデルにテクスチャを張り付ける
	//MV1SetTextureGraphHandle(*duplicateModel, 0, texture, FALSE);

	//移動予定地点と移動する距離の初期化
	targetPos = position.x;
	moveDistance = 0;

	//モデルを保存し描画するComponentを実装
	ModelComponent * modelComponent;
	modelComponent = new ModelComponent(this);
	//Game::GetInstance()->AddModel(modelComponent);
	int modelId = Game::GetInstance()->LoadModel("model/whiteBall.mqo");
	modelComponent->SetModel(modelId);
	scale = 0.1f;
	modelComponent->SetModelScale(scale);
}


Player::~Player()
{
	//MV1DeleteModel(*duplicateModel);
	//delete duplicateModel;
	//duplicateModel = NULL;
}

void Player::Move()
{
	//移動中でない場合のみ入力を受け付ける
	if (position.x == targetPos)
	{
		//生成時に受け取ったキーが入力されたとき
		if (Game::GetInstance()->GetAllInputKey()[moveInThisKey] == 1)
		{
			//移動予定地
			targetPos = position.x + (MovingDistance*nextMoveDirection);
			//1Fで移動する距離
			moveDistance = (((position.x + nextMoveDirection) - position.x) / MovingDistance);
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
		position.x += moveDistance;
	}
}

void Player::UpdateActor(float deltaTime)
{
	//回転させる
	rotation = VAdd(rotation, VGet(0.1f, 0, 0));
}
