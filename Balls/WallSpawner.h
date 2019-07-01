#pragma once

#include "DxLib.h"

class Wall;
class Actor;

class WallSpawner
{
public:
	WallSpawner();
	~WallSpawner();
	void WallSpawn();
	bool ballWallCollision(Actor* ball);
private:
	int count;
	const int SpawnTime = 50;
	//Wall�̃A�h���X��ۑ����Ă���
	Wall* walls[50];
	//����State��Pausing��Wall���擾
	Wall* GetPausingWall();
	//��̃��[���̂ǂ���ɐݒu���邩�������_���Ŏ擾����
	VECTOR CreateWallPosition();
};

