#pragma once
#include "MoveComponent.h"


class HeadForTargetComponent :
	public MoveComponent
{
public:
	HeadForTargetComponent(Actor* owner, int processNumber, VECTOR distance, VECTOR rotateSpeed);
	~HeadForTargetComponent();

	void HeadForTarget(float deltaTime);
	void SetTargetPos(const VECTOR& target);
	void SetMoveSpeed(const VECTOR& speed);
private:
	VECTOR ownerPos;
	VECTOR targetPos;
	VECTOR moveSpeed;
	float CulculationVector(const float& pos, const float& target);
};

