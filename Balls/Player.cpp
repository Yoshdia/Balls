#include "Player.h"
#include <math.h>
#include "ModelComponent.h"
#include "MovePlayerComponent.h"
#include "Game.h"
#include "SphereColliderComponent.h"

Player::Player(VECTOR initPos, Game::MoveDirection next, char moveKey)
{
	position = initPos;

	//ƒ‚ƒfƒ‹‚ð•Û‘¶‚µ•`‰æ‚·‚éComponent‚ðŽÀ‘•
	ModelComponent * modelComponent;
	modelComponent = new ModelComponent(this);
	int modelId = Game::GetInstance()->LoadModel("Resouce/model/ball.mqo","Resouce/img/box.png");
	modelComponent->SetModel(modelId);
	scale = VGet(0.01f, 0.01f, 0.01f);
	modelComponent->SetModelScale(scale);

	MovePlayerComponent * movePlayerComponent;
	movePlayerComponent = new MovePlayerComponent(this, 101, moveKey, next);

	sphereCollider = new SphereColliderComponent(this, 150, 0.01f);
	Game::GetInstance()->AddSphereCollider(sphereCollider);
}


Player::~Player()
{
	Game::GetInstance()->RemoveSphereCollider(sphereCollider);
}

void Player::UpdateActor(float deltaTime)
{
	//‰ñ“]‚³‚¹‚é
	rotation = VAdd(rotation, VGet(0.1f, 0, 0));
}
