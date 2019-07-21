#include "CountDownComponent.h"

CountDownComponent::CountDownComponent(int max) :
	nowCount(max),
	maxCount(max)
{
}

CountDownComponent::~CountDownComponent()
{
}

bool CountDownComponent::CountEnd()
{
	if (nowCount <= 0)
	{
		return true;
	}
	else
	{
		nowCount--;
		return false;
	}
}
