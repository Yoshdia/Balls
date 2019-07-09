#pragma once

#include "Dxlib.h"
#include "Game.h"
#include "Actor.h"

class 	SphereColliderComponent;
class 	MovePlayerComponent;
class ModelComponent;

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

