#include "SlowlyChangeScaleComponent.h"
#include "Actor.h"

SlowlyChangeScaleComponent::SlowlyChangeScaleComponent(Actor * owner, int updateOrder) :
	ModelComponent(owner, updateOrder),
	updating(false),
	scale(OriginScale),
	increaseScale(OriginScale)
{
}

SlowlyChangeScaleComponent::SlowlyChangeScaleComponent(Actor * owner, int setProcessNumber, VECTOR scale, const std::string & fileName) :
	ModelComponent(owner, setProcessNumber, scale, fileName),
	updating(false),
	scale(OriginScale),
	increaseScale(OriginScale)
{
}

SlowlyChangeScaleComponent::~SlowlyChangeScaleComponent()
{
}

void SlowlyChangeScaleComponent::Update(float deltaTime)
{
	if (!updating)
	{
		return;
	}


	VECTOR ownerScale = ownerActor->GetScale();
	float x = CulculationScale(ownerScale.x, scale.x);
	float y = CulculationScale(ownerScale.y, scale.y);
	float z = CulculationScale(ownerScale.z, scale.z);

	if (!x && !y && !z)
	{
		updating = false;
		return;
	}

	ownerScale.x += x * increaseScale.z;
	ownerScale.y += y * increaseScale.y;
	ownerScale.z += z * increaseScale.z;

	SetModelScale(ownerScale);
	ownerActor->SetScale(ownerScale);
}

float SlowlyChangeScaleComponent::CulculationScale(const float & ownerScale, const float & targetScale)
{
	if (ownerScale == targetScale)
	{
		return 0;
	}

	bool plus = ownerScale < targetScale;
	float plusScale = 1;
	if (plus)
	{
		plusScale *= 1;
	}
	else
	{
		plusScale *= -1;
	}
	return plusScale;
}

void SlowlyChangeScaleComponent::StartCoroutine(const VECTOR& howManyScale, const float& howMuchTime)
{
	updating = true;
	scale = howManyScale;

	VECTOR ownerScale = ownerActor->GetScale();

	//必ずsubScale内の値がプラスになるように差を求める
	VECTOR leftScale = VGet(ownerScale.x < howManyScale.x ? howManyScale.x : ownerScale.x,
							ownerScale.y < howManyScale.y ? howManyScale.y : ownerScale.y,
							ownerScale.z < howManyScale.z ? howManyScale.z : ownerScale.z);
	VECTOR rightScale = VGet(ownerScale.x < howManyScale.x ? ownerScale.x : howManyScale.x,
							ownerScale.y < howManyScale.y ? ownerScale.y : howManyScale.y,
							ownerScale.z < howManyScale.z ? ownerScale.z : howManyScale.z);
	VECTOR subScale= VSub(leftScale, rightScale);

	increaseScale.x = subScale.x / howMuchTime;
	increaseScale.y = subScale.y / howMuchTime;
	increaseScale.z = subScale.z / howMuchTime;

}

