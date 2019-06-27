#pragma once
#include "Actor.h"
class Ground :
	public Actor
{
public:
	Ground(VECTOR initPos);
	~Ground();
	void UpdateComponents(float deltaTime);
};

