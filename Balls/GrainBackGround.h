#pragma once

#include "Actor.h"
class MoveComponent;

class GrainBackGround :
	public Actor
{
public:
	GrainBackGround();
	~GrainBackGround();

	void ResetBackGround(VECTOR pos,VECTOR target);
	void UpdateActor(float deltaTime);
private:
	VECTOR targetPos;
	MoveComponent* moveComponent;
};

