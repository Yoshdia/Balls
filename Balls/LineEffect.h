#pragma once
#include "Actor.h"


class LineEffect :
	public Actor
{
public:
	LineEffect();
	~LineEffect();

	void ResetLine(VECTOR pos);
	void UpdateActor(float deltaTime);

private:
	VECTOR endPos;
	static const float LineValue;
	static const VECTOR MoveSpeed;
};

