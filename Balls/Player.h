#pragma once

#include "Dxlib.h"
#include "Game.h"
#include "Actor.h"


class SphereColliderComponent;
class MovePlayerComponent;
class ModelComponent;
class CountDownComponent;
class SlowlyChangeScaleComponent;

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
	SphereColliderComponent* sphereCollider;
	CountDownComponent* countDownComponent;
	CountDownComponent* superLikelyCountDownComponent;
	SlowlyChangeScaleComponent* modelAndSlowlyChangeScaleComponent;
	static const VECTOR normalModelScale;
	static const VECTOR superModelScale;

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

