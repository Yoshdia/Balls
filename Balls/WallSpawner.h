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
	void WallSpawn(float deltaTime);
	//���ׂĂ�wall�̈ړ����~������������߂�����
	void WallStop();

	//���ׂĂ�wall��������Ԃɖ߂�
	void WallClear();
private:
	float count=0;
	const float SpawnTime = 60;
	float spawnTime;
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
	VECTOR CreateWallPositionCreateSuperWall(int rand);
	void CreateSuperWall(int rand, int rightOrLeft);

};

