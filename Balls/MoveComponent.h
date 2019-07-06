#pragma once
#include "Component.h"
class Actor;

class MoveComponent :
	public Component
{
public:
	MoveComponent(Actor* owner ,int processNumber, VECTOR distance);
	~MoveComponent();
	void Update(float deltaTime);
protected:
	static float gameSpeed;
	void Move(float deltaTime);
	VECTOR position;
	//–ˆFˆÚ“®‚·‚é‹——£
	VECTOR moveDistance;
};

