#include "Wall.h"
#include "ModelComponent.h"
#include "HeadForTargetComponent.h"
#include "Renderer.h"

Wall::Wall(BoxColliderComponent::ColliderTag tag,const std::string& modelFileName)
{
	position = InitPos;

	scale = VGet(0.01f, 0.01f, 0.001f);
	ModelComponent * modelComponent;
	modelComponent = new ModelComponent(this,200, scale, modelFileName);

	headForTarget = new HeadForTargetComponent(this, 102, moveSpeed,VGet(0,0,0));

	boxCollider = new BoxColliderComponent(this, 150, 0.02f, tag);
	boxCollider->SetIsCollision(false);
}

Wall::~Wall()
{
}

void Wall::UpdateActor(float deltaTime)
{
	headForTarget->HeadForTarget(deltaTime);
	if (position.z <= -2)
	{
		boxCollider->SetIsCollision(false);
	}
	else if (position.z <= 0)
	{
		boxCollider->SetIsCollision(true);
	}
	if (position.z < -10)
	{
		state = Actor::ActiveState::Paused;
	}
}


void Wall::ResetWall(VECTOR pos, VECTOR target)
{
	position = pos;

	state = Actor::ActiveState::Active;
	boxCollider->SetIsCollision(false);
	headForTarget->SetTargetPos(target);
	headForTarget->SetMoveSpeed(moveSpeed);
}

void Wall::ClearWall()
{
	SetPosition(InitPos);
	state = Actor::ActiveState::Paused;
	boxCollider->SetIsCollision(false);
}

void Wall::StopMove()
{
	headForTarget->SetMoveSpeed(VGet(0,0,0));
}

void Wall::OnCollision()
{
	ClearWall();
}

