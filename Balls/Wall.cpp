#include "Wall.h"
#include "ModelComponent.h"
#include "MoveComponent.h"

Wall::Wall()
{
	position = VGet(1, 0, 10);

	ModelComponent * modelComponent;
	modelComponent = new ModelComponent(this);
	int modelId = Game::GetInstance()->LoadModel("model/wall.mqo", "model/grade.JPG");
	modelComponent->SetModel(modelId);
	scale = 0.2f;
	modelComponent->SetModelScale(scale);

	MoveComponent * moveComponent;
	moveComponent = new MoveComponent(this, 102, VGet(0, 0, -0.1f));
	

	comeOutCamera = false;
}

Wall::~Wall()
{

}

void Wall::UpdateActor(float deltaTime)
{
	if (position.z < -10)
	{
		comeOutCamera=true;
	}
}


void Wall::ResetWall(float x)
{
	//pos = VGet(x, 0, 10);
	//comeOutCamera = false;

}
