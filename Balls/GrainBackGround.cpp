#include "GrainBackGround.h"
#include "MoveComponent.h"


GrainBackGround::GrainBackGround()
{
	moveComponent = new MoveComponent(this,120,VGet(0, 0, 0),VGet(0,0,0));

	ResetBackGround(VGet(50,0,-100),VGet(0,0,0));
}


GrainBackGround::~GrainBackGround()
{
}

void GrainBackGround::ResetBackGround(VECTOR pos, VECTOR target)
{
	SetPosition(pos);
	targetPos = target;

}

void GrainBackGround::UpdateActor(float deltaTime)
{
	if (position.z < 0)
	{
		moveComponent->SetMoveSpeed(VGet(0, 0, 0));
	}
}
