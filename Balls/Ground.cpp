#include "Ground.h"
#include "ModelComponent.h"
#include "Renderer.h"

Ground::Ground(VECTOR initPos)
{
	position = initPos;

	scale = VGet(0.04f, 0.01f, 1.0f);
	ModelComponent * modelComponent;
	modelComponent = new ModelComponent(this, 90, scale ,"Resouce/model/ground.mv1" );

}


Ground::~Ground()
{
}

void Ground::UpdateComponents(float deltaTime)
{
}
