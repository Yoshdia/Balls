#include "SphereColliderComponent.h"
#include "Actor.h"
#include "Collider.h"

SphereColliderComponent::SphereColliderComponent(Actor * owner, int processNumber, float length)
	:Component(owner,processNumber)
	,info({owner->GetPosition(),length})
	,myTag(SphereColliderComponent::CollisionTag::NormalPlayer)
{
	Collider::GetInstance()->AddSphereCollider(this);
}

SphereColliderComponent::~SphereColliderComponent()
{
	Collider::GetInstance()->RemoveSphereCollider(this);
}

void SphereColliderComponent::OnCollision()
{
	 ownerActor->OnCollision();
}

void SphereColliderComponent::Update(float deltaTime)
{
	UpdatePosition();
}

void SphereColliderComponent::UpdatePosition()
{
	info.position = ownerActor->GetPosition();
}
