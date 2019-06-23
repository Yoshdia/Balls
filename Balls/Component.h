#pragma once
#include "Game.h"

class Actor;

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual     ~Component();
	virtual void Update(float deltaTime);                              // �R���|�[�l���g��deltaTime�ōX�V
	int          getUpdateOrder() const { return mUpdateOrder; }       // �X�V�������擾

protected:
	class Actor* mOwner;            // ���L�A�N�^�[
	int          mUpdateOrder;      // �X�V����
	int          mCreateIndex;      // �쐬�ʂ��ԍ�
	static int   mNo;               // �R���|�[�l���g�쐬�J�E���^
};