#pragma once
#include "Game.h"

class Wall 
{
public:
	Wall();
	~Wall();

	void Update();
	void Render();
	//���W���󂯎�����n�_�ɂ��A�t���O��|��
	void ResetWall(float x);

	bool GetComeOutCameraFlag() { return comeOutCamera; };
private:
	float movingSpeed;
	//�J�����̊O�ɏo���猚�t���O�Btrue�őҋ@��Ԃɖ߂�
	bool comeOutCamera;

	VECTOR pos;
	int *model;
	int *duplicateModel;
	int *modelTexture;
};

