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
	modelComponent = new ModelComponent(this);
	superModelId = Game::GetInstance()->LoadModel("Resouce/model/superBall.mv1");
	normalModelId = Game::GetInstance()->LoadModel("Resouce/model/ball.mv1");
	modelComponent->SetModel(normalModelId);
	scale = VGet(0.01f, 0.01f, 0.01f);
	modelComponent->SetModelScale(scale);

	MovePlayerComponent * movePlayerComponent;
	movePlayerComponent = new MovePlayerComponent(this, 101, moveKey, next);

	sphereCollider = new SphereColliderComponent(this, 150, 0.01f);

	superCount = 0;
	super = false;
}

Player::~Player()
{
}

void Player::UpdateActor(float deltaTime)
{
	//‰ñ“]‚³‚¹‚é
	rotation = VAdd(rotation, VGet(5.0f*deltaTime, 0, 0));
	if (super)
	{
		superCount--;
		if (superCount < 0)
		{
			super = false;
			ChangeModel();
		}
	}
}

void Player::OnCollision()
{
	ChangeModel();
}

void Player::ChangeModel()
{
	if (sphereCollider->GetTag() == SphereColliderComponent::CollisionTag::SuperPlayer)
	{
 		modelComponent->SetModel(normalModelId);
		modelComponent->SetModelScale(scale);

		sphereCollider->TagChange(SphereColliderComponent::CollisionTag::NormalPlayer);
	}
	else
	{
		modelComponent->SetModel(superModelId);
		modelComponent->SetModelScale(scale);

		super = true;
		superCount = superCountMax;

		sphereCollider->TagChange(SphereColliderComponent::CollisionTag::SuperPlayer);
	}
}
