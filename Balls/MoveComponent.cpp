#include "DxLib.h"
#include "MoveComponent.h"
#include "Actor.h"
#include "Game.h"


MoveComponent::MoveComponent(Actor * owner, int processNumber, VECTOR distance, VECTOR rotateSpeed) :
	Component(owner, processNumber)
	, position(owner->GetPosition())
	, moveDistance(distance)
	, rotationSpeed(rotateSpeed)
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltaTime)
{
	Move(deltaTime);
	Rotate(deltaTime);
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
	position = ownerActor->GetPosition();

	VECTOR distance = moveDistance;
	distance = distance * deltaTime;
	distance = distance * gameSpeed;

	position = VAdd(position, distance);
	ownerActor->SetPosition(position);
}

void MoveComponent::Rotate(float deltaTime)
{
	VECTOR rotation = ownerActor->GetRotation();
	rotation = VAdd(rotation, rotationSpeed*deltaTime);
	ownerActor->SetRotation(rotation);
}
