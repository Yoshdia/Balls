#pragma once
#include "Shape.h"
class SphereShape :
	public Shape
{
public:
	SphereShape();
	~SphereShape();

	void ResetSphere(VECTOR pos, float range,bool fill);
private:
	void UpdateBack(float deltaTime);
	float range;
	static const float zSpeed;
	bool fill;
	static const VECTOR MoveSpeed;
};

