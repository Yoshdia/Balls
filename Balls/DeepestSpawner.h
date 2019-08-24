#pragma once

class GrainBackGroundHaver;
class WallCreateAndHaver;
class Wall;
#include "Actor.h"
class HeadForTargetComponent;
class CountDownComponent;
class Camera;

//�X�e�[�W�̉�����wall��grain���Y�ݏo���N���X
class DeepestSpawner
	:public Actor
{
public:
	DeepestSpawner(Camera* pCamera);
	~DeepestSpawner();

	void SpawnerUpdate(float deltaTime);
	void UpdateActor(float deltaTime);
	//���ׂĂ�Object�̈ړ����~������������߂�����
	void StopDeepestObject();
	//���ׂĂ�Object��������Ԃɖ߂�
	void ClearDeepestObject();
	//��~������ړ����ĊJ������
	void ReStartDeepestObject();
private:
	Camera* camera;
	//GameSpees�N���X����󂯎����gameSpeed����v�Z���������b��
	float plusSpeed;

	enum GrainShade
	{
		sphere,
		square,
	};
	GrainShade grainShade;

	HeadForTargetComponent* headForTargetComponent;
	CountDownComponent* countDownComponent;
	CountDownComponent* groundSpawnCountDown;
	CountDownComponent* boxSpawnCountDown;
	CountDownComponent* randomSpawnCountDown;
	//moving�t���O���|��Ă���Ƃ��Ɏ��s�����A���ړ����������肷��֐�
	void CreateMovePlan();
	//�ő吔
	static const int CreateMovePlanCntMax;
	//AdjacentTargetX������܂ňړ��\�ɂ��邩
	static const float MoveStage;
	//1��ňړ�����傫��
	static const VECTOR AdjacentTarget;

	static const VECTOR MovingSpeed;

	//�w�i��grain�N���X
	GrainBackGroundHaver* grainCreateAndHaver;
	//�w�i��grain���Y�ݏo��
	void GrainSpawn(float deltaTime);
	void SphereGrain(VECTOR grainMiddlePos);
	//void SquareGrain(VECTOR grainMiddlePos,char plusOrMinas);
	void MonotoneGrain(VECTOR grainMiddlePos,char plusOrMinas);
	void GroundGrain(VECTOR grainMiddlePos);
	//void RamdamGrain();
	static const float SpawnRandomMaxCount;

	//grain���Y�ݏo��y���W ������������
	static const float GrainHeight;
	//grain���~��ɎY�ݏo���ۂ̔��a
	static const float Radius;

	static const float SpawnGroundTime;
	static const float SpawnBoxTime;

	static const float squareHeight;
	static const int GroundGrainHeight;

	//wall���m�ۂ��Ă���N���X
	WallCreateAndHaver* wallCreateAndHaver;
	//SpawnTime���Ƃ�wall�𐶐�����֐�
	void WallSpawn(float deltaTime);
	//�ݒu����
	void SetWall();
	//wall���Y�ݏo���C���^�[�o��
	float wallCount;

	//�ǂ�wall��ݒu�����邩��I������֐�
	Wall* GetRandomWall();
	//���ꂼ���Wall���ݒu�����m��
	static const int WallRandMax;
	static const float AddPointRand;
	static const float AddSpeedRand;
	//�ݒu�C���^�[�o���̏�����
	static const float SpawnTime;
	//�ݒu�C���^�[�o���̑�����̒l������
	float spawnTime;
	static const VECTOR StartRunPos;
	//��̃��[���̂ǂ���ɐݒu���邩�������_���Ŏ擾����
	VECTOR CreateWallPositionCreateSuperWall(int rand);
	void CreateSuperWall(int rand, int rightOrLeft);
};

