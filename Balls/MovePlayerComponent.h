#pragma once

#include "MoveComponent.h"
class Actor;
class Game;

class MovePlayerComponent :
	protected MoveComponent
{
public:
	//�ړ������m����moveKey�A���߂ɂǂ���ֈړ����邩��next���w��
	MovePlayerComponent(Actor* owner,int processNumber, char moveKey, Game::MoveDirection next,VECTOR rotateSpeed);
	~MovePlayerComponent();
	void Update(float deltaTime);

	void StartCorutine();
	void StopCorutine() { updating = false; }
	void SetMoveDirection(Game::MoveDirection next) { nextMoveDirection = next; }
protected:

	bool updating;
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
	//�ړ������̓񕪂̈�
	float middlePos;

	//�ړ�����F
	static const float MovingRequiredTime ;
	//�ړ�����
	static const float MovingDistanceSum ;
};

