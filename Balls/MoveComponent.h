#pragma once
#include "Component.h"
class Actor;

class MoveComponent :
	public Component
{
public:
	MoveComponent(Actor* owner ,int processNumber);
	~MoveComponent();
protected:
	VECTOR position;
	//–ˆFˆÚ“®‚·‚é‹——£
	VECTOR moveDistance;
	void Move(float deltaTime);
};

