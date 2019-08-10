#pragma once

class GrainBackGroundHaver;
class WallCreateAndHaver;
class Wall;

//�X�e�[�W�̉�����wall��grain���Y�ݏo���N���X
class DeepestSpawner
{
public:
	DeepestSpawner();
	~DeepestSpawner();

	void SpawnerUpdate(float deltaTime);

	//���ׂĂ�Object�̈ړ����~������������߂�����
	void StopDeepestObject();
	//���ׂĂ�Object��������Ԃɖ߂�
	void ClearDeepestObject();
	//��~������ړ����ĊJ������
	void ReStartDeepestObject();
private:
	//���̃N���X�̒��S���W
	VECTOR myPos;
	//GameSpees�N���X����󂯎����gameSpeed����v�Z���������b��
	float plusSpeed;

	enum GrainShade
	{
		sphere,
		square,
	};
	GrainShade grainShade;

	//�ړ������ǂ���
	bool moving;
	//moving�t���O�������Ă���Ƃ��Ɏ��s���ꑱ����֐�
	void Move();
	//moving�t���O���|��Ă���Ƃ��Ɏ��s�����A���ړ����������肷��֐�
	void CreateMovePlan();
	//�֐����ĂԃJ�E���g
	int createMovePlanCnt;
	//�ő吔
	static const int CreateMovePlanCntMax;
	//����ړ�������W
	float targetPositionX;
	//AdjacentTargetX������܂ňړ��\�ɂ��邩
	static const float MoveStage;
	//1��ňړ�����傫��
	static const float AdjacentTargetX;
	float CulculationX();
	static const float movingSpeed;

	//�w�i��grain�N���X
	GrainBackGroundHaver* grainCreateAndHaver;
	//�w�i��grain���Y�ݏo��
	void GrainSpawn(float deltaTime);
	//�ݒu
	void SetGrain();
	void SphereGrain(VECTOR grainMiddlePos);
	void SquareGrain(VECTOR grainMiddlePos,char plusOrMinas);

	//grain���Y�ݏo���C���^�[�o��
	float grainCount;

	//grain���Y�ݏo��y���W ������������
	static const float GrainHeight;
	//grain���~��ɎY�ݏo���ۂ̔��a
	static const float Radius;
	static const float SpawnGrainTime;

	static const float squareHeight;

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

