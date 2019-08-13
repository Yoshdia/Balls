#include "SphereColliderComponent.h"
#include "Actor.h"
#include "Collider.h"
#include "EffectFactory.h"


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

void SphereColliderComponent::OutOfScreen()
{
	EffectFactory::GetInstance()->PopEffect(ownerActor->GetPosition(), EffectFactory::Effects::Block);
	ownerActor->SetPosition(VGet(0, 10, 0));
}

void SphereColliderComponent::UpdatePosition()
{
	info.position = ownerActor->GetPosition();
}
