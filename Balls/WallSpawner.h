#pragma once

#include "DxLib.h"

class Wall;
class AddSpeedWall;
class AddPointWall;

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
	int RandamSpawnWallMax = 200;
	//Wall�̃A�h���X��ۑ����Ă���
	Wall* walls[50];
	//AddSpeedWall�ւ̃A�h���X
	AddSpeedWall* addSpeedWalls[5];
	//AddPointWall
	AddPointWall* addPointWalls[5];
	//����State��Pausing��Wall���擾
	Wall* GetPausingWall();
	//��̃��[���̂ǂ���ɐݒu���邩�������_���Ŏ擾����
	VECTOR CreateWallPosition();

	static const VECTOR InitPos;
};

