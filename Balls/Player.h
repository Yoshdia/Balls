#pragma once

#include "Object.h"
//��ʎ�O�ō��E�Ɉړ����鋅�B����������
class Player:
	protected Object
{
public:
	//���̃I�u�W�F�N�g���ǂ���̌����֐i�ނ̂��̗񋓑́B�ړ�����MovingDistance�ɒ��ڏ�Z����
	enum PlayerMoveDirection
	{
		RightMove = 1,
		LeftMove = -1,
	};
	//�������W�A���߂ɐi�ޕ���(���E)�A�ړ��̃g���K�[�ɂȂ�L�[���󂯎��ۑ�����
	Player(VECTOR initPos, PlayerMoveDirection next, char moveKey);
	~Player();

	void Update();
	void Render();
private:
	PlayerMoveDirection nextMoveDirection;

	//�ړ��\��n�_
	float targetPos;
	//��F�ړ����鋗��
	float moveDistance;
	//Game����󂯎��A���̃I�u�W�F�N�g���������������ƂȂ�L�[
	char moveInThisKey;
	//�ړ������֐�
	void Move();
	//��]���鑬�x
	VECTOR rotate;

	//�ړ�����
	const float movingRequiredTime = 10;
	//�ړ�����
	const float MovingDistance = 2;
};
