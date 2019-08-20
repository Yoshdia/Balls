#include "HeadForTargetComponent.h"
#include "Actor.h"


HeadForTargetComponent::HeadForTargetComponent(Actor * owner, int processNumber, VECTOR distance, VECTOR rotateSpeed)
	:MoveComponent(owner,processNumber,distance,rotateSpeed)
	,targetPos(VGet(0,0,0))
	,ownerPos(VGet(0,0,0))
	,moveSpeed(distance)
{
	xxxxx = 3;
	yyyyy = 3;
}

HeadForTargetComponent::~HeadForTargetComponent()
{
}

void HeadForTargetComponent::HeadForTarget(float deltaTime)
{
	ownerPos = ownerActor->GetPosition();
	float x=CulculationVector(ownerPos.x, targetPos.x);
	float y=CulculationVector(ownerPos.y, targetPos.y);
	float z=CulculationVector(ownerPos.z, targetPos.z);
	xxxxx -= 0.01f;
	if (xxxxx < 0.01f)
	{
		xxxxx = 0.01f;
	}
	yyyyy -= 0.01f;
	if (yyyyy < 1)
	{
		yyyyy == 0.01f;
	}
	VECTOR speed = VGet((xxxxx*xxxxx)*x, (yyyyy*yyyyy)*y, z*moveSpeed.z);
	MoveComponent::SetMoveSpeed(speed);

	Move(deltaTime);
}

void HeadForTargetComponent::SetTargetPos(const VECTOR& target)
{
	targetPos = target;
	xxxxx = 3;
	yyyyy = 3;
}

void HeadForTargetComponent::SetMoveSpeed(const VECTOR& speed)
{
	moveSpeed = speed;
	MoveComponent::SetMoveSpeed(speed);
}

float HeadForTargetComponent::CulculationVector(const float& pos,const float& target)
{
	bool plus = pos < target ? true : false;
	float plusPos = 1;

	if (plus)
	{
		if (target > pos)
		{
			plusPos *=1;
		}
		else
		{
			plusPos *= 0;
		}
	}
	else
	{
		if (target < pos)
		{
			plusPos *= -1;
		}
		else
		{
			plusPos *= 0;
		}
	}
	return plusPos;
}

