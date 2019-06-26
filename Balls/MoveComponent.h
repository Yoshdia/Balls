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
	//��F�ړ����鋗��
	VECTOR moveDistance;
	void Move(float deltaTime);
};

