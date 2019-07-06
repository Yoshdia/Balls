#include "DxLib.h"
#include "Game.h"
#include "MovePlayerComponent.h"
#include "Actor.h"

MovePlayerComponent::MovePlayerComponent(Actor * owner, int processNumber, char moveKey, Game::MoveDirection next)
	:MoveComponent(owner, processNumber, VGet(0, 0, 0))
	, nextMoveDirection(next)
	, targetPos(owner->GetPosition().x)
	, moveInputeKey(moveKey)
	, moving(false)
	,movement(MovingDistance)
	,middlePos((float)2*next)
{
}

MovePlayerComponent::~MovePlayerComponent()
{
}

void MovePlayerComponent::Update(float deltaTime)
{
	//移動中でない場合のみ入力を受け付ける
	if (!moving)
	{
		//インスタンス生成時に受け取ったmoveInputKeyが入力されたとき
		if (Game::GetInstance()->GetAllInputKey()[moveInputeKey] == 1)
		{
			//移動予定地の計算
			targetPos = middlePos + (MovingDistance/2*nextMoveDirection);
			//残り移動距離
			movement = targetPos-position.x;
			//1fに移動する距離
			moveDistance.x = movement * movingRequiredTime;
			//残り移動距離を絶対値に変換
			movement = abs(movement);
			//右に移動していた場合左に　のように左右切り替えられるようにする
			switch (nextMoveDirection)
			{
			case(Game::MoveDirection::Right):nextMoveDirection = Game::MoveDirection::Left; break;
			case(Game::MoveDirection::Left):nextMoveDirection = Game::MoveDirection::Right; break;
			}
			moving = true;
		}
	}
	else
	{
		Move(deltaTime);
		//残り移動距離が0になるまで移動を続ける
		movement -= (moveDistance.x*deltaTime)*-nextMoveDirection;
		if (movement<=0)
		{
			position.x = targetPos;
			ownerActor->SetPosition(position);
			moving = false;
		}
	}
}
