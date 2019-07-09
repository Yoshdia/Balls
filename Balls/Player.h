#pragma once

#include "Dxlib.h"
#include "Game.h"
#include "Actor.h"

class 	SphereColliderComponent;
class 	MovePlayerComponent;
class ModelComponent;

//��ʎ�O�ō��E�Ɉړ����鋅�B����������
class Player:
	public Actor
{
public:
	//�������W�A���߂ɐi�ޕ���(���E)�A�ړ��̃g���K�[�ɂȂ�L�[���w��
	Player(VECTOR initPos, Game::MoveDirection next, char moveKey);
	~Player();

	void UpdateActor(float deltaTime);
	//�Փˎ��̓��f����ύX����
	void OnCollision();
private:	
	ModelComponent * modelComponent;
	SphereColliderComponent* sphereCollider;
	int normalModelId;
	int superModelId;
	void ChangeModel();
	int superCount;
	bool super;
	const int superCountMax=180;
};

