#pragma once
#include "Game.h"
#include "Actor.h"
#include "DxLib.h"

class BoxColliderComponent;

class Wall :
	public Actor
{
public:
	Wall(VECTOR initPos);
	~Wall();

	void UpdateActor(float deltaTime);

	//���W���󂯎�����n�_�ɂ��A�t���O��|��
	void ResetWall(VECTOR pos);
	bool GetComeOutCameraFlag() { return comeOutCamera; };
private:
	BoxColliderComponent* boxCollider;
	//�J�����̊O�ɏo���猚�t���O�Btrue�őҋ@��Ԃɖ߂�
	bool comeOutCamera;
};

