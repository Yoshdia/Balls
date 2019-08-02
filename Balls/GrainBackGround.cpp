#include "GrainBackGround.h"
#include "MoveComponent.h"
#include "ModelComponent.h"

GrainBackGround::GrainBackGround()
{
	ResetBackGround(VGet(0,2,0),VGet(0,0,0));

	moveComponent = new MoveComponent(this,120,VGet(0, 0, 0),VGet(0,0,0));

	scale = VGet(0.001f, 0.001f, 0.001f);
	ModelComponent* modelComponent;
	modelComponent = new ModelComponent(this, 150, scale,"Resouce/model/normalSphere.mv1");
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
		//moveComponent->SetMoveSpeed(VGet(0, 0, 5));
	}
}
