#pragma once
#include "Wall.h"
//�v���C���[�ƐڐG�����MoveComponent���ɂ���ÓI�����o��gameSpeed�����Z�����
class AddSpeedWall :
	public Wall
{
public:
	AddSpeedWall(VECTOR initPos);
	~AddSpeedWall();
	void OnCollision();
};

