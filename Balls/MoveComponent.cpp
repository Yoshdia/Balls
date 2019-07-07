#include "DxLib.h"
#include "MoveComponent.h"
#include "Actor.h"
#include "Game.h"


MoveComponent::MoveComponent(Actor * owner, int processNumber, VECTOR distance) :
	Component(owner, processNumber)
	, position(owner->GetPosition())
	, moveDistance(distance)
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltaTime)
{
	Move(deltaTime);
}

void MoveComponent::Move()
{
	position = ownerActor->GetPosition();
	VECTOR distance = VGet(
		moveDistance.x,
		moveDistance.y,
		moveDistance.z
	);
	position = VAdd(position, distance);
	ownerActor->SetPosition(position);
}

void MoveComponent::Move(float deltaTime)
{
	float gameSpeed = Game::GetInstance()->GetGameSpeed();
	position=ownerActor->GetPosition();
	VECTOR distance = VGet(
		moveDistance.x*deltaTime*gameSpeed,
		moveDistance.y*deltaTime*gameSpeed,
		moveDistance.z*deltaTime*gameSpeed
	);

	position = VAdd(position, distance);
	ownerActor->SetPosition(position);
}
