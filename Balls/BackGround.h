#pragma once
#include "Actor.h"

class HeadForTargetComponent;

class BackGround :
	public Actor
{
public:
	BackGround(const VECTOR& moveSpeed);
	virtual ~BackGround();

	void UpdateActor(float deltaTime);
	void MoveReStart();
	void StopMove();
protected:
	void ResetBackGround(VECTOR pos, VECTOR target);
	virtual void UpdateBack(float deltaTime);
	VECTOR targetPos;
	HeadForTargetComponent* headForTarget;

	VECTOR moveSpeed;

	bool moving;
};

