#pragma once

#include "Object.h"
#include "Game.h"

//��ʎ�O�ō��E�Ɉړ����鋅�B����������
class Player:
	protected Object
{
public:

	//�������W�A���߂ɐi�ޕ���(���E)�A�ړ��̃g���K�[�ɂȂ�L�[���󂯎��ۑ�����
	Player(VECTOR initPos, Game::MoveDirection next, char moveKey,int model,int texture);
	~Player();

	void Update();
	void Render();
private:
	Game::MoveDirection nextMoveDirection;

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

	VECTOR pos;

	int *duplicateModel;


	//�ړ�����
	const float movingRequiredTime = 10;
	//�ړ�����
	const float MovingDistance = 2;
};

