#pragma once
#include "BackGround.h"

class MoveComponent;

class Shape :
	public BackGround
{
public:
	Shape(VECTOR moveSpeed);
	virtual ~Shape();
};

