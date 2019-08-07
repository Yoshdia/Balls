#pragma once

#include "Actor.h"
class HeadForTargetComponent;

class GrainBackGround :
	public Actor
{
public:
	GrainBackGround();
	~GrainBackGround();

	void ResetBackGround(VECTOR pos,VECTOR target);
	void UpdateActor(float deltaTime);
	void StopMove();

	void MoveReStart();
private:
	VECTOR targetPos;
	HeadForTargetComponent* headForTarget;

	bool moving;
};

