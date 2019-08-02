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
	//float throwAngle;
	//VECTOR CalculateVelocity(const VECTOR& pointA, const VECTOR& pointB);
	//VECTOR Determine();

	//VECTOR offset;
	//VECTOR target;
	//float a;
	//float b;
	//float ab;

	float SetX();
	void SetY();

	float z;
	
};

