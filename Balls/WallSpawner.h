#pragma once

#include "DxLib.h"
class WallCreateAndHaver;
class Wall;

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
	//Wall���m�ۂ��Ă���N���X
	WallCreateAndHaver* wallCreateAndHaver;
	//�ǂ�ݒu����
	void WallsSpawn();
	//�ǂ̕ǂ�ݒu�����邩��I������֐�
	Wall* GetRandomWall();
	//���ꂼ���Wall���ݒu�����m��
	static const int WallRandMax;
	static const float AddPointRand;
	static const float AddSpeedRand;
	//�ݒu�̃^�C�~���O�𐶐�����J�E���g
	float count;
	//�ݒu�C���^�[�o���̏�����
	static const float SpawnTime;
	//�ݒu�C���^�[�o���̑�����̒l������
	float spawnTime;
	//
	//int RandamSpawnWallMax = 200;
	const VECTOR StartRunPos = VGet(1, 0, 100);

	//��̃��[���̂ǂ���ɐݒu���邩�������_���Ŏ擾����
	VECTOR CreateWallPositionCreateSuperWall(int rand);
	void CreateSuperWall(int rand, int rightOrLeft);
};

