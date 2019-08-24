#pragma once
#include "MoveComponent.h"

//�֐��Ŏ󂯎�����^�[�Q�b�g�Ɍ���������
class HeadForTargetComponent :
	public MoveComponent
{
public:
	HeadForTargetComponent(Actor* owner, int processNumber, VECTOR distance, VECTOR rotateSpeed);
	~HeadForTargetComponent();

	//�ړ����x��ݒ�
	void SetMoveSpeed(const VECTOR& speed);
	//�^�[�Q�b�g�̍X�V
	void SetTargetPos(const VECTOR& target);
	//�^�[�Q�b�g�Ɍ����������A��F�Ă�
	void HeadForTarget(float deltaTime);
	//using MoveComponent::SetMoveSpeed;
private:
	VECTOR ownerPos;
	VECTOR targetPos;
	VECTOR moveSpeed;
	float CulculationVector(float& pos, float& target,bool plusAddPosition);

	float plusX;
	bool plusAddPosition[3];
};

