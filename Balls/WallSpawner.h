#pragma once

#include "DxLib.h"

class Wall;
class AddSpeedWall;

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
	const int SpawnTime = 60;
	int spawnTime;
	int AddWallRandam = 200;
	//Wall�̃A�h���X��ۑ����Ă���
	Wall* walls[50];
	//AddWall�ւ̃A�h���X
	AddSpeedWall* addWalls[5];
	//����State��Pausing��Wall���擾
	Wall* GetPausingWall();
	//��̃��[���̂ǂ���ɐݒu���邩�������_���Ŏ擾����
	VECTOR CreateWallPosition();
};

