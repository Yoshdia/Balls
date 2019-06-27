#include "DxLib.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor * owner, int processNumber,VECTOR distance):
	Component(owner,processNumber)
	,position(owner->GetPosition())
	,moveDistance(distance)
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltaTime)
{
	Move(deltaTime);
}

void MoveComponent::Move(float deltaTime)
{
	position=ownerActor->GetPosition();
	position = VAdd(position,moveDistance);
	ownerActor->SetPosition(position);
}
