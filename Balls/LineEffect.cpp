#include "LineEffect.h"
#include "MoveComponent.h"

const float LineEffect::LineValue = 10;
const VECTOR LineEffect::MoveSpeed = VGet(0,0,-60);

LineEffect::LineEffect()
{
	SetState(Actor::ActiveState::Paused);
	MoveComponent* moveComponent;
	moveComponent = new MoveComponent(this, 300, MoveSpeed, OriginQua);
}


LineEffect::~LineEffect()
{
}

void LineEffect::ResetLine(VECTOR pos)
{
	SetState(Actor::ActiveState::Active);
	SetPosition(pos);
}

void LineEffect::UpdateActor(float deltaTime)
{
	endPos = position;
	endPos.z += LineValue;
	DrawLine3D(position, endPos, GetColor(255, 255, 255));
	if (position.z < -LineValue*2)
	{
		SetState(Actor::ActiveState::Paused);
	}
}
