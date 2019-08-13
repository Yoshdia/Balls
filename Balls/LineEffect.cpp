#include "LineEffect.h"
#include "MoveComponent.h"

const float LineEffect::LineValue = 10;
const float LineEffect::zSpeed = -60;

LineEffect::LineEffect():
	endPos(OriginPos)
{
	SetState(Actor::ActiveState::Paused);
	MoveComponent* moveComponent;
	moveComponent = new MoveComponent(this, 100, VGet(0, 0, zSpeed), OriginQua);
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
	if (position.z < -20)
	{
		SetState(Actor::ActiveState::Paused);
	}
	DrawLine3D(position, endPos, GetColor(255, 255, 255));
}

