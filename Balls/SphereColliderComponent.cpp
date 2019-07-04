#include "SphereColliderComponent.h"
#include "Actor.h"
#include "Game.h"

SphereColliderComponent::SphereColliderComponent(Actor * owner, int processNumber, float length)
	:Component(owner,processNumber)
{
	Game::GetInstance()->AddSphereCollider(this);
	info = { owner->GetPosition(),length };
}

SphereColliderComponent::~SphereColliderComponent()
{
	Game::GetInstance()->RemoveSphereCollider(this);
}

void SphereColliderComponent::Update(float deltaTime)
{
	UpdatePosition();
}

void SphereColliderComponent::UpdatePosition()
{
	info.position = ownerActor->GetPosition();
}
