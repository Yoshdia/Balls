#include "DxLib.h"
#include "Game.h"
#include "MovePlayerComponent.h"

MovePlayerComponent::MovePlayerComponent(Actor * owner, int processNumber, char moveKey, Game::MoveDirection next)
	:MoveComponent(owner,processNumber,VGet(0,0,0))
	,nextMoveDirection(next)
	,targetPos(position.x)
	,moveInputeKey(moveKey)
{
}

MovePlayerComponent::~MovePlayerComponent()
{
}

void MovePlayerComponent::Update(float deltaTime)
{
	//移動中でない場合のみ入力を受け付ける
	if (position.x == targetPos)
	{
		//生成時に受け取ったキーが入力されたとき
		if (Game::GetInstance()->GetAllInputKey()[moveInputeKey] == 1)
		{
			//移動予定地
			targetPos = position.x + (MovingDistance*nextMoveDirection);
			//1Fで移動する距離
			moveDistance.x = (((position.x + nextMoveDirection) - position.x) / MovingDistance);
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
		Move(deltaTime);
	}
}
