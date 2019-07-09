#pragma once

#include "DxLib.h"

class Wall;
class AddSpeedWall;
class AddPointWall;
class SuperWall;

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
	const VECTOR StartRunPos = VGet(1, 0, 100);
	//Wall�̃A�h���X��ۑ����Ă���
	Wall* walls[50];
	//�����Wall�ւ̃A�h���X
	AddSpeedWall* addSpeedWalls[5];
	AddPointWall* addPointWalls[5];
	SuperWall* superWalls[5];
	//����State��Pausing��Wall���擾
	Wall* GetPausingWall();
	//��̃��[���̂ǂ���ɐݒu���邩�������_���Ŏ擾����
	VECTOR CreateWallPositionCreateSuperWall();
	void CreateSuperWall(int rand);

	static const VECTOR InitPos;
};

