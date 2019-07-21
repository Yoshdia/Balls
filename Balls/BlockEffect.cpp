#include "BlockEffect.h"
#include "MoveComponent.h"
#include "ModelComponent.h"
#include "CountDownComponent.h"

const float BlockEffect::RoundDistance = 30.0f;
const int BlockEffect::LifeCntMax =20;

BlockEffect::BlockEffect():
	lifeCnt(0)
{
	countDownComponent = new CountDownComponent(LifeCntMax);

	moveComponent = new MoveComponent(this, 150, VGet(0,0,0), VGet(0, 0, 30));
	
	scale = VGet(0.005f, 0.005f, 0.005f);
	ModelComponent* modelComponent;
	modelComponent = new ModelComponent(this, 200, scale, "Resouce/model/sui.mv1");

	SetState(Actor::ActiveState::Paused);
}

BlockEffect::~BlockEffect()
{
}

void BlockEffect::UpdateActor(float deltaTime)
{
 	if (countDownComponent->CountEnd())
	{
		SetState(Actor::ActiveState::Paused);
	}
}

void BlockEffect::ResetBlock(VECTOR setMiddlePos, BlockMoveDirection dir)
{
	SetState(Actor::ActiveState::Active);
	SetPosition(setMiddlePos);
	VECTOR dis = VGet(0, 0, 0);

	dis.x += RoundDistance/2;
	dis.y += RoundDistance/3;

	if (dir== BlockMoveDirection::RightUp ||dir== BlockMoveDirection::RightDown)
	{
		dis.y *= -1;
	}
	if (dir== BlockMoveDirection::LeftDown || dir== BlockMoveDirection::RightDown)
	{
		dis.x *= -1;
	}
	moveComponent->SetMoveSpeed(dis); 
	countDownComponent->ResetCount();
}
