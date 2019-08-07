#include "HeadForTargetComponent.h"
#include "Actor.h"


HeadForTargetComponent::HeadForTargetComponent(Actor * owner, int processNumber, VECTOR distance, VECTOR rotateSpeed)
	:MoveComponent(owner,processNumber,distance,rotateSpeed)
	,targetPos(VGet(0,0,0))
	,ownerPos(VGet(0,0,0))
	,moveSpeed(VGet(0,0,0))
{
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
	VECTOR speed = VGet(x, y, z)*moveSpeed;
	MoveComponent::SetMoveSpeed(speed);

	Move(deltaTime);
}

void HeadForTargetComponent::SetTargetPos(const VECTOR& target)
{
	targetPos = target;

}

void HeadForTargetComponent::SetMoveSpeed(const VECTOR& speed)
{
	moveSpeed = speed;
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
