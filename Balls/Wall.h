#pragma once
#include "Game.h"
#include "Actor.h"

class Wall :
	public Actor
{
public:
	Wall(VECTOR initPos);
	~Wall();

	void UpdateActor(float deltaTime);

	//���W���󂯎�����n�_�ɂ��A�t���O��|��
	void ResetWall(float x);
	bool GetComeOutCameraFlag() { return comeOutCamera; };
private:
	//�J�����̊O�ɏo���猚�t���O�Btrue�őҋ@��Ԃɖ߂�
	bool comeOutCamera;
};

