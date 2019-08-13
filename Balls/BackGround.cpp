#include "BackGround.h"
#include "HeadForTargetComponent.h"

//const VECTOR BackGround::MoveSpeed = VGet(5, 5, 30.0f);
//const VECTOR BackGround::MoveSpeed = VGet(1.0f, 1.0f, 5.0f);


BackGround::BackGround(const VECTOR& moveSpeed):
	moveSpeed(moveSpeed)
{
	headForTarget = new HeadForTargetComponent(this, 120, VGet(0, 0, 0), VGet(0, 0, 0));
	SetState(Actor::ActiveState::Paused);
	moving = false;
}

BackGround::~BackGround()
{
}

void BackGround::UpdateActor(float deltaTime)
{
	UpdateBack(deltaTime);
	if (moving)
	{
		headForTarget->SetMoveSpeed(moveSpeed);
		headForTarget->HeadForTarget(deltaTime);
	}

	if (position.z < -20)
	{
		SetState(Actor::ActiveState::Paused);
	}
}

void BackGround::MoveReStart()
{
	moving = true;
}

void BackGround::StopMove()
{
	moving = false;
	headForTarget->MoveComponent::SetMoveSpeed(VGet(0, 0, 0));
}

void BackGround::ResetBackGround(VECTOR pos, VECTOR target)
{
	SetPosition(pos);
	headForTarget->SetTargetPos(target);
	SetState(Actor::ActiveState::Active);
	moving = true;
}

void BackGround::UpdateBack(float deltaTime)
{
}
