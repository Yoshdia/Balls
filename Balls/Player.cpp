#include "Player.h"
#include <math.h>
#include "ModelComponent.h"
#include "MovePlayerComponent.h"
#include "Game.h"
#include "SphereColliderComponent.h"
#include "CountDownComponent.h" 

Player::Player(VECTOR initPos, Game::MoveDirection next, char moveKey)
{
	position = initPos;

	scale = VGet(0.01f, 0.01f, 0.01f);
	//モデルを保存し描画するComponentを実装(後々使用するsuperBallのモデルはScaleを変更するためここでSetする)
	modelComponent = new ModelComponent(this);
	superModelId = Game::GetInstance()->LoadModel("Resouce/model/superBall.mv1");
	modelComponent->SetModel(normalModelId);
	modelComponent->SetModelScale(scale);

	normalModelId = Game::GetInstance()->LoadModel("Resouce/model/ball.mv1");
	modelComponent->SetModel(normalModelId);
	modelComponent->SetModelScale(scale);

	MovePlayerComponent * movePlayerComponent;
	movePlayerComponent = new MovePlayerComponent(this, 101, moveKey, next, VGet(5.0f, 0, 0));

	sphereCollider = new SphereColliderComponent(this, 150, 0.01f);

	countDownComponent = new CountDownComponent(superCountMax);
}

Player::~Player()
{
}

void Player::UpdateActor(float deltaTime)
{
	if (countDownComponent->CountEnd())
	{
		ChangeNormalModel();
	}
}

void Player::OnCollision()
{
	ChangeSuperModel();
}

void Player::ChangeNormalModel()
{
	//モデルを変更
	modelComponent->SetModel(normalModelId);
	modelComponent->SetModelScale(scale);
	//タグを変更
	sphereCollider->TagChange(SphereColliderComponent::CollisionTag::NormalPlayer);
}

void Player::ChangeSuperModel()
{
	//モデルを変更
	modelComponent->SetModel(superModelId);
	modelComponent->SetModelScale(scale);

	//タグを変更
	sphereCollider->TagChange(SphereColliderComponent::CollisionTag::SuperPlayer);

	countDownComponent->ResetCount();
}

