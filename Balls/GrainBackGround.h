#pragma once

#include "Actor.h"
class HeadForTargetComponent;
class ModelComponent;

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

	enum GrainColor
	{
		Red,
		white,
	};
	void ColorChange(GrainColor color);
private:
	VECTOR targetPos;
	HeadForTargetComponent* headForTarget;
	ModelComponent* modelComponent;

	static const VECTOR MoveSpeed;

	int redModel;
	int whiteModel;

	bool moving;
};

