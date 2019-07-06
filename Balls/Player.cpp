#include "Player.h"
#include <math.h>
#include "ModelComponent.h"
#include "MovePlayerComponent.h"
#include "Game.h"
#include "SphereColliderComponent.h"

Player::Player(VECTOR initPos, Game::MoveDirection next, char moveKey)
{
	position = initPos;

	//モデルを保存し描画するComponentを実装
	ModelComponent * modelComponent;
	modelComponent = new ModelComponent(this);
	int modelId = Game::GetInstance()->LoadModel("Resouce/model/ball.mqo","Resouce/img/box.png");
	modelComponent->SetModel(modelId);
	scale = VGet(0.01f, 0.01f, 0.01f);
	modelComponent->SetModelScale(scale);

	MovePlayerComponent * movePlayerComponent;
	movePlayerComponent = new MovePlayerComponent(this, 101, moveKey, next);

	SphereColliderComponent* sphereCollider;
	sphereCollider = new SphereColliderComponent(this, 150, 0.01f);
}


Player::~Player()
{
}

void Player::UpdateActor(float deltaTime)
{
	//回転させる
	rotation = VAdd(rotation, VGet(0.1f, 0, 0));
}
