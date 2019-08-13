#pragma once

#include "Dxlib.h"
#include "Game.h"
#include "Actor.h"


class SphereColliderComponent;
class MovePlayerComponent;
class ModelComponent;
class CountDownComponent;
class SlowlyChangeScaleComponent;
class HeadForTargetComponent;

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

	void StartMove();
	void StopMove();
	void SetFirstPosition();
	void MoveFirstPosition(float deltaTime);
	void SkipMoveFirstPosition();
private:	
	MovePlayerComponent* movePlayerComponent;
	SphereColliderComponent* sphereCollider;
	CountDownComponent* countDownComponent;
	CountDownComponent* superLikelyCountDownComponent;
	SlowlyChangeScaleComponent* modelAndSlowlyChangeScaleComponent;
	HeadForTargetComponent* headForFirstPosition;

	static const VECTOR normalModelScale;
	static const VECTOR superModelScale;
	VECTOR firstPosition;
	Game::MoveDirection firstDirection;
	static const VECTOR MoveSpeed;

	int normalModelId;
	int superModelId;
	//Player�̏�ԕω�
	void LikelyChangeNormalModel();
	void ChangeNormalModel();
	void ChangeSuperModel();

	static const int superCountMax;
	static const int superEndLikeryCount;
	static const int superEndCount;

};

