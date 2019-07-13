#include "Wall.h"
#include "ModelComponent.h"
#include "MoveComponent.h"

Wall::Wall(BoxColliderComponent::ColliderTag tag,const std::string& modelFileName)
{
	position = InitPos;

	ModelComponent * modelComponent;
	modelComponent = new ModelComponent(this, 200);
	int modelId = 0;
	modelId = Game::GetInstance()->LoadModel(modelFileName);

	modelComponent->SetModel(modelId);
	scale = VGet(0.01f, 0.01f, 0.001f);
	modelComponent->SetModelScale(scale);

	moveComponent = new MoveComponent(this, 102, moveSpeed,VGet(0,0,0));

	boxCollider = new BoxColliderComponent(this, 150, 0.02f, tag);
	boxCollider->SetIsCollision(false);
}

Wall::~Wall()
{
}

void Wall::UpdateActor(float deltaTime)
{
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


void Wall::ResetWall(VECTOR pos)
{
	position = pos;
	state = Actor::ActiveState::Active;
	boxCollider->SetIsCollision(false);
	moveComponent->SetMoveSpeed(moveSpeed);
}

void Wall::ClearWall()
{
	SetPosition(InitPos);
	state = Actor::ActiveState::Paused;
	boxCollider->SetIsCollision(false);
}

void Wall::StopMove()
{
	moveComponent->SetMoveSpeed(VGet(0,0,0));
}

void Wall::OnCollision()
{
	ClearWall();
}

