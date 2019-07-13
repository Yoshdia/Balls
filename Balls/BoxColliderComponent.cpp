#include "BoxColliderComponent.h"
#include "Actor.h"
#include "Collider.h"


BoxColliderComponent::BoxColliderComponent(Actor * owner, int processNumber, float length, ColliderTag tag)
	:Component(owner, processNumber)
	,myTag(tag)
{
	Collider::GetInstance()->AddBoxCollider(this);
	info = { owner->GetPosition(),length };
}

BoxColliderComponent::~BoxColliderComponent()
{
	Collider::GetInstance()->RemoveCollider(this);
}

void BoxColliderComponent::Update(float deltaTime)
{
	UpdatePosition();
}

void BoxColliderComponent::OnCollision()
{

	ownerActor->OnCollision(); 

}

void BoxColliderComponent::UpdatePosition()
{
	info.position = ownerActor->GetPosition();
}


