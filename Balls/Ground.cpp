#include "Ground.h"
#include "ModelComponent.h"


Ground::Ground(VECTOR initPos)
{
	position = initPos;

	ModelComponent * modelComponent;
	modelComponent = new ModelComponent(this, 90);
	int modelId = Game::GetInstance()->LoadModel("model/ground.mqo", "model/grade.JPG");
	modelComponent->SetModel(modelId);
	scale = 0.1f;
	modelComponent->SetModelScale(scale);

}


Ground::~Ground()
{
}

void Ground::UpdateComponents(float deltaTime)
{
}
