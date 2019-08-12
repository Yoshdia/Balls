#include "CountDownComponent.h"

CountDownComponent::CountDownComponent(int max) :
	nowCount(max),
	maxCount(max),
	updating(false)
{
}

CountDownComponent::~CountDownComponent()
{
}

bool CountDownComponent::CountEnd()
{
	if (updating)
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
	return false;
}

void CountDownComponent::ResetCount()
{
	updating = true;
	nowCount = maxCount;
}
