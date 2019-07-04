#include "Wall.h"
#include "ModelComponent.h"
#include "MoveComponent.h"

Wall::Wall(VECTOR initPos)
{
	position = initPos;

	ModelComponent * modelComponent;
	modelComponent = new ModelComponent(this,120);
	int modelId = Game::GetInstance()->LoadModel("Resouce/model/wall.mqo", "Resouce/img/wall.png");
	modelComponent->SetModel(modelId);
	scale = VGet(0.02f, 0.02f, 0.01f);
	modelComponent->SetModelScale(scale);

	MoveComponent * moveComponent;
	moveComponent = new MoveComponent(this, 102, VGet(0, 0, -1.0f));
	

	comeOutCamera = false;
}

Wall::~Wall()
{

}

void Wall::UpdateActor(float deltaTime)
{
	if (position.z < -10)
	{
		state = Actor::ActiveState::NoActive;
	}
}


void Wall::ResetWall(VECTOR pos)
{
	position=pos;
	state = Actor::ActiveState::Active;
}
