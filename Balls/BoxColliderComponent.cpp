#include "BoxColliderComponent.h"
#include "Actor.h"
#include "Game.h"


BoxColliderComponent::BoxColliderComponent(Actor * owner, int processNumber, float length)
	:Component(owner, processNumber)
{
	Game::GetInstance()->AddBoxCollider(this);
	info = { owner->GetPosition(),length };
}

BoxColliderComponent::~BoxColliderComponent()
{
	Game::GetInstance()->RemoveCollider(this);
}

void BoxColliderComponent::Update(float deltaTime)
{
	updatePosition();
}

void BoxColliderComponent::updatePosition()
{
	info.position = ownerActor->GetPosition();
}
