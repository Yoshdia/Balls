#include "BoxShape.h"

//const VECTOR BoxShape::MoveSpeed = VGet(1.0f,1.0f,5.0f);
const VECTOR BoxShape::MoveSpeed = VGet(5.0f, 5.0f, 30.0f);

BoxShape::BoxShape():
	Shape(MoveSpeed),
	height(OriginPos)
{
	SetState(Actor::ActiveState::Paused);
}

BoxShape::~BoxShape()
{
}

void BoxShape::ResetBox(VECTOR pos, VECTOR targetPos,VECTOR height, bool fill)
{
	SetPosition(pos);
	SetState(Actor::ActiveState::Active);
	this->height = height;
	this->fill = fill;
	ResetBackGround(pos, targetPos);
}

void BoxShape::UpdateBack(float deltaTime)
{
	VECTOR LeftDown =position;
	LeftDown.y -= height.y;
	VECTOR RightUp  =position;
	RightUp.z += height.z;
	VECTOR RightDown=position;
	RightDown.y -= height.y;
	RightDown.z += height.z;
	
	DrawLine3D(position, LeftDown, GetColor(255, 255, 255));
	DrawLine3D(LeftDown, RightDown, GetColor(255, 255, 255));
	DrawLine3D(RightDown, RightUp, GetColor(255, 255, 255));
	DrawLine3D(RightUp, position, GetColor(255, 255, 255));
}
