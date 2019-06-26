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
	Game::MoveDirection nextMoveDirection;
	//�ړ��\��n�_
	float targetPos;
	//Game����󂯎��A���̃I�u�W�F�N�g���������������ƂȂ�L�[
	char moveInputeKey;

	//�ړ�����
	const float movingRequiredTime = 10;
	//�ړ�����
	const float MovingDistance = 2;
};

