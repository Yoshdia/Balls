#pragma once

#include "DxLib.h"

class Wall;

class WallSpawner
{
public:
	WallSpawner();
	~WallSpawner();
	//SpawnTime���Ƃ�Wall�𐶐�����֐�
	void WallSpawn();
	//���ׂĂ�wall�̈ړ����~������������߂�����
	void WallStop();
	//���ׂĂ�wall��������Ԃɖ߂�
	void WallClear();
private:
	int count;
	const int SpawnTime = 50;
	int spawnTime;
	//Wall�̃A�h���X��ۑ����Ă���
	Wall* walls[50];
	//����State��Pausing��Wall���擾
	Wall* GetPausingWall();
	//��̃��[���̂ǂ���ɐݒu���邩�������_���Ŏ擾����
	VECTOR CreateWallPosition();
};

