#include "HeadForTargetComponent.h"
#include "Actor.h"


HeadForTargetComponent::HeadForTargetComponent(Actor * owner, int processNumber, VECTOR distance, VECTOR rotateSpeed)
	:MoveComponent(owner, processNumber, distance, rotateSpeed)
	, targetPos(VGet(0, 0, 0))
	, ownerPos(VGet(0, 0, 0))
	, moveSpeed(distance)
	,plusX(0)
{
	
}

HeadForTargetComponent::~HeadForTargetComponent()
{
}

void HeadForTargetComponent::HeadForTarget(float deltaTime)
{
	ownerPos = ownerActor->GetPosition();
	float x=CulculationVector(ownerPos.x, targetPos.x,plusAddPosition[0]);
	//float y=CulculationVector(ownerPos.y, targetPos.y,plusAddPosition[1]);
	float y = 0;
	float z=CulculationVector(ownerPos.z, targetPos.z, plusAddPosition[2]);
	plusX-=0.01f;
	if (plusX < 0)
	{
		plusX = 0.1f;
	}

	VECTOR speed = VGet((plusX*plusX)*x,(plusX*plusX)* y, z*moveSpeed.z);
	MoveComponent::SetMoveSpeed(speed);

	Move(deltaTime);
}

void HeadForTargetComponent::SetTargetPos(const VECTOR& target)
{
	targetPos = target;
	plusX = sqrt(moveSpeed.x);
	
	plusAddPosition[0] = false;
	plusAddPosition[1] = false;
	plusAddPosition[2] = false;

	//plusAddPosition[0] = position.x < target.x ? true : false;
	//plusAddPosition[1] = position.y < target.y ? true : false;
	//plusAddPosition[2] = position.z < target.z ? true : false;
	//if (plusAddPosition[0])
	//{
	//	int a = 0;
	//}
}

void HeadForTargetComponent::SetMoveSpeed(const VECTOR& speed)
{
	moveSpeed = speed;
	MoveComponent::SetMoveSpeed(speed);
}

float HeadForTargetComponent::CulculationVector(float& pos,float& target, bool plusAddPosition)
{
	if (plusAddPosition)
	{
		return 0;
	}
	bool plus = pos < target ? true : false;
	float plusPos = 1;

	if (plus)
	{
		if (target > pos)
		{
			plusPos *= 1;
		}
		else
		{
			plusPos *= 0;
			plusAddPosition = true;
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
			plusAddPosition = true;
		}
	}
	return plusPos;

	//if (plusAddPosition)
	//{
	//	if (pos > target)
	//	{
	//		//pos = target;
	//		return 0;
	//	}
	//	return 1;
	//}
	//else
	//{
	//	if (pos < target)
	//	{
	//		//pos = target;
	//		return 0;
	//	}
	//	return -1;
	//}
}

