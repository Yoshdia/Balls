#include "SphereShape.h"

const VECTOR SphereShape::MoveSpeed = VGet(1,1,1);

SphereShape::SphereShape() :
	Shape(MoveSpeed),
	range(0)
{
	SetState(Actor::ActiveState::Paused);

}


SphereShape::~SphereShape()
{
}

void SphereShape::ResetSphere(VECTOR pos,VECTOR targetPos ,float range,bool fill)
{
	SetPosition(pos);	
	SetState(Actor::ActiveState::Active);
	this->range = range;
	this->fill = fill;
	ResetBackGround(pos, targetPos);
}

void SphereShape::UpdateBack(float deltaTime)
{
	DrawSphere3D(position, range, 20, GetColor(255, 255, 255), GetColor(255, 255, 255), fill);
}
