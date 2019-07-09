#include "Ground.h"
#include "ModelComponent.h"


Ground::Ground(VECTOR initPos)
{
	position = initPos;

	ModelComponent * modelComponent;
	modelComponent = new ModelComponent(this, 90);
	int modelId = Game::GetInstance()->LoadModel("Resouce/model/ground.mv1");
	modelComponent->SetModel(modelId);
	scale = VGet(0.04f,0.01f,1.0f);
	modelComponent->SetModelScale(scale);

}


Ground::~Ground()
{
}

void Ground::UpdateComponents(float deltaTime)
{
}
