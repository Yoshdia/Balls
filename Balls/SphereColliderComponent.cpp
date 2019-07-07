#include "SphereColliderComponent.h"
#include "Actor.h"
#include "Game.h"

SphereColliderComponent::SphereColliderComponent(Actor * owner, int processNumber, float length)
	:Component(owner,processNumber)
	,info({owner->GetPosition(),length})
	,myTag(SphereColliderComponent::CollisionTag::NormalPlayer)
{
	Game::GetInstance()->AddSphereCollider(this);
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
