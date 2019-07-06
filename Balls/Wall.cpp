#include "Wall.h"
#include "ModelComponent.h"
#include "MoveComponent.h"
#include "BoxColliderComponent.h"

Wall::Wall(VECTOR initPos)
{
	position = initPos;

	ModelComponent * modelComponent;
	modelComponent = new ModelComponent(this,120);
	int modelId = Game::GetInstance()->LoadModel("Resouce/model/wall.mv1", "Resouce/img/wall.png");
	modelComponent->SetModel(modelId);
	scale = VGet(0.01f, 0.01f, 0.001f);
	modelComponent->SetModelScale(scale);

	MoveComponent * moveComponent;
	moveComponent = new MoveComponent(this, 102, VGet(0, 0, -60.0f));
	
	boxCollider = new BoxColliderComponent(this, 150, 0.02f);
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
	position=pos;
	state = Actor::ActiveState::Active;
	boxCollider->SetIsCollision(false);
}

void Wall::ClearWall()
{
	position = VGet(0, -10, 0);
	state = Actor::ActiveState::Paused;
	boxCollider->SetIsCollision(false);
}
