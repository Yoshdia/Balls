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

//画面手前で左右に移動する球。二つ生成される
class Player:
	public Actor
{
public:
	//初期座標、初めに進む方向(左右)、移動のトリガーになるキーを指定
	Player(VECTOR initPos, Game::MoveDirection next, char moveKey);
	~Player();

	void UpdateActor(float deltaTime);
	//衝突時はモデルを変更する
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
	//Playerの状態変化
	void LikelyChangeNormalModel();
	void ChangeNormalModel();
	void ChangeSuperModel();

	static const int superCountMax;
	static const int superEndLikeryCount;
	static const int superEndCount;

};

