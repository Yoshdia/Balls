#include "DxLib.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor * owner, int processNumber):
	Component(owner,processNumber)
	,position(owner->GetPosition())
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Move(float deltaTime)
{
	position=ownerActor->GetPosition();
	position = VAdd(position,moveDistance);
	ownerActor->SetPosition(position);
}
