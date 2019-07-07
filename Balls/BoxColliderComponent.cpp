#include "BoxColliderComponent.h"
#include "Actor.h"
#include "Game.h"


BoxColliderComponent::BoxColliderComponent(Actor * owner, int processNumber, float length, ColliderTag tag)
	:Component(owner, processNumber)
	,myTag(tag)
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

void BoxColliderComponent::OnCollision()
{
	 ownerActor->OnCollision(); 
}

void BoxColliderComponent::updatePosition()
{
	info.position = ownerActor->GetPosition();
}
