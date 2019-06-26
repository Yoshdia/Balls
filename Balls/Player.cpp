#include "Player.h"
#include <math.h>
#include "ModelComponent.h"
#include "MovePlayerComponent.h"
#include "Game.h"

Player::Player(VECTOR initPos, Game::MoveDirection next, char moveKey)
{
	position = initPos;

	//モデルを保存し描画するComponentを実装
	ModelComponent * modelComponent;
	modelComponent = new ModelComponent(this);
	int modelId = Game::GetInstance()->LoadModel("model/whiteBall.mqo","model/grade.JPG");
	modelComponent->SetModel(modelId);
	scale = 0.1f;
	modelComponent->SetModelScale(scale);

	MovePlayerComponent * movePlayerComponent;
	movePlayerComponent = new MovePlayerComponent(this, 101, moveKey, next);
}


Player::~Player()
{
}




void Player::UpdateActor(float deltaTime)
{
	//回転させる
	rotation = VAdd(rotation, VGet(0.1f, 0, 0));
}
