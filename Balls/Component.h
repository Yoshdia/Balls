#pragma once
#include "Game.h"

class Actor;

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void Update(float deltaTime);                              // �R���|�[�l���g��deltaTime�ōX�V
	// �X�V������Ԃ�
	int getProccesNumber() const { return processNumber; } //getUpdateOrder
protected:
	//����Component�����L���Ă���Actor�ւ̃A�h���X
	class Actor* ownerActor;//owner
	// �X�V����
	int processNumber;//mUpdateOrder
	//int mCreateIndex;      // �쐬�ʂ��ԍ�
	// �R���|�[�l���g���쐬�����Ƒ�����J�E���g
	static int componentCount;//mNo
};