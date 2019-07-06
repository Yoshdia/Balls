#pragma once

#include "MoveComponent.h"
class Actor;
class Game;

class MovePlayerComponent :
	protected MoveComponent
{
public:
	MovePlayerComponent(Actor* owner,int processNumber, char moveKey, Game::MoveDirection next);
	~MovePlayerComponent();
	void Update(float deltaTime);
protected:
	//���̈ړ�����
	Game::MoveDirection nextMoveDirection;
	//�ړ��\��n�_
	float targetPos;
	//Game����󂯎��A���̃I�u�W�F�N�g���������������ƂȂ�L�[
	char moveInputeKey;
	//�ړ������ǂ���
	bool moving ;
	//�c��̈ړ������A0�ɂȂ��moving��|��
	float movement;

	float middlePos;

	//�ړ�����F
	const float movingRequiredTime = 10.0f;
	//�ړ�����
	const float MovingDistance = 2.0f;
};

