#pragma once
#include "Shape.h"
class BoxShape :
	public Shape
{
public:
	BoxShape();
	~BoxShape();

	void ResetBox(VECTOR pos, VECTOR targetPos, VECTOR height, bool fill);
private:
	void UpdateBack(float deltaTime);
	VECTOR height;
	bool fill;
	static const VECTOR MoveSpeed;
};

