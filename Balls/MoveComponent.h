#pragma once

#include "Component.h"
class Actor;

//�󂯎����distance��Actor�̍��W�ɉ��Z��������Component
class MoveComponent :
	public Component
{
public:
	MoveComponent(Actor* owner ,int processNumber, VECTOR distance, VECTOR rotateSpeed);
	~MoveComponent();
	void Update(float deltaTime);
	void SetRotationSpeed(VECTOR speed) { rotationSpeed = speed; };
	void SetMoveSpeed(VECTOR speed) { moveDistance = speed; }
protected:
	//���W��moveDistance�𑫂������̊֐�
	void Move(float deltaTime);
	//��]����֐�
	void Rotate(float deltaTime);

	//�p���悩��Ă΂��AdeltaTime���p����Ōv�Z���邽�߈�����֐�����deltaTime���Ȃ�Move�֐�
	void Move();
	VECTOR position;
	//��F�ړ����鋗��
	VECTOR moveDistance;

	VECTOR rotationSpeed;
};

