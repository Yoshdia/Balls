#pragma once

#include "Dxlib.h"
#include "Game.h"
#include "Actor.h"

//��ʎ�O�ō��E�Ɉړ����鋅�B����������
class Player:
	public Actor
{
public:
	//�������W�A���߂ɐi�ޕ���(���E)�A�ړ��̃g���K�[�ɂȂ�L�[���󂯎��ۑ�����
	Player(VECTOR initPos, Game::MoveDirection next, char moveKey,int texture);
	~Player();

	void UpdateActor(float deltaTime);
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
	//�ړ�����
	const float movingRequiredTime = 10;
	//�ړ�����
	const float MovingDistance = 2;
};

