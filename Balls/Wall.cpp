#include "Wall.h"
#include "ModelComponent.h"
#include "MoveComponent.h"

Wall::Wall(VECTOR initPos, BoxColliderComponent::ColliderTag tag)
{
	position = initPos;

	ModelComponent * modelComponent;
	modelComponent = new ModelComponent(this, 200);
	int modelId = 0;
	switch (tag)
	{
	case(BoxColliderComponent::ColliderTag::AddSpeedWall):
		modelId = Game::GetInstance()->LoadModel("Resouce/model/addSpeedWall.mv1", "Resouce/img/wall.png");
		break;
	case(BoxColliderComponent::ColliderTag::JammerWall):
		modelId = Game::GetInstance()->LoadModel("Resouce/model/wall.mv1", "Resouce/img/wall.png");
		break;
	case(BoxColliderComponent::ColliderTag::AddPointWall):
		modelId = Game::GetInstance()->LoadModel("Resouce/model/plusWall.mv1", "Resouce/img/wall.png");
	case(BoxColliderComponent::ColliderTag::SuperWall):
		modelId = Game::GetInstance()->LoadModel("Resouce/model/superItem.mv1", "Resouce/img/wall.png");
		break;
	}
	modelComponent->SetModel(modelId);
	scale = VGet(0.01f, 0.01f, 0.001f);
	modelComponent->SetModelScale(scale);

	moveComponent = new MoveComponent(this, 102, VGet(0, 0, -60.0f));

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
}

void Wall::ClearWall()
{
	SetPosition(InitPos);
	state = Actor::ActiveState::Paused;
	boxCollider->SetIsCollision(false);
}

void Wall::OnCollision()
{
	ClearWall();
}

