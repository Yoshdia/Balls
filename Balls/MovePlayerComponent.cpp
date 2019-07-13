#include "DxLib.h"
#include "InputKey.h"
#include "MovePlayerComponent.h"
#include "Actor.h"

const float MovePlayerComponent::MovingRequiredTime = 10.0f;
const float MovePlayerComponent::MovingDistanceSum = 2.0f;

MovePlayerComponent::MovePlayerComponent(Actor * owner, int processNumber, char moveKey, Game::MoveDirection next, VECTOR rotateSpeed)
	:MoveComponent(owner, processNumber, VGet(0, 0, 0),rotateSpeed)
	, nextMoveDirection(next)
	, targetPos(owner->GetPosition().x)
	, moveInputeKey(moveKey)
	, moving(false)
	,movement(MovingDistanceSum)
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
		if (InputKey::GetInstance()->GetAllInputKey()[moveInputeKey] == 1)
		{
			//移動予定地の計算
			targetPos = middlePos + (MovingDistanceSum/2*nextMoveDirection);
			//残り移動距離
			movement = targetPos-position.x;
			//float gameSpeed = Game::GetInstance()->GetGameSpeed();
			float gameSpeed = 1.0f;
			//1fに移動する距離
			moveDistance.x = (movement * MovingRequiredTime)*deltaTime*gameSpeed;
			//MoveComponent内のgameSpeedが一定以上まで上昇すると移動距離が合計移動距離を上回ることがあるため上限値を設定
			if (moveDistance.x >= MovingDistanceSum)
			{
				moveDistance.x = MovingDistanceSum;
			}
			//残り移動距離を絶対値に変換
			movement = abs(movement);
			//移動先を左右切り替える
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
		//MoveComponent内の、値を計算させる関数へ
		Move();
		//残り移動距離が0になるまで移動を続ける
		movement -= moveDistance.x*-nextMoveDirection;
		if (movement<=0)
		{
			position.x = targetPos;
			ownerActor->SetPosition(position);
			moving = false;
		}
	}
	Rotate(deltaTime);
}
