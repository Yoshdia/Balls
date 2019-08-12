#include "Player.h"
#include <math.h>
#include "ModelComponent.h"
#include "MovePlayerComponent.h"
#include "Renderer.h"
#include "SphereColliderComponent.h"
#include "CountDownComponent.h" 
#include "SlowlyChangeScaleComponent.h"

const VECTOR Player::normalModelScale = VGet(0.01f, 0.01f, 0.01f);
//const VECTOR Player::normalModelScale = VGet(10, 10, 10);
const VECTOR Player::superModelScale = VGet(0.02f, 0.02f, 0.02f);
//const VECTOR Player::superModelScale = VGet(10, 10, 10);

const int Player::superCountMax=180;
const int Player::superEndLikeryCount=50;
const int Player::superEndCount= Player::superCountMax- Player::superEndLikeryCount;

Player::Player(VECTOR initPos, Game::MoveDirection next, char moveKey)
{
	position = initPos;

	scale = VGet(0.01f, 0.01f, 0.01f);
	//���f����ۑ����`�悷��Component������(��X�g�p����superBall�̃��f����������Scale��Set���Ă���)
	//modelComponent = new ModelComponent(this,ModelComponent::DrawPlayerNumber);
	modelAndSlowlyChangeScaleComponent = new SlowlyChangeScaleComponent(this, 200);

	superModelId = Renderer::GetInstance()->LoadModel("Resouce/model/superBall.mv1");
	modelAndSlowlyChangeScaleComponent->SetModel(superModelId);
	modelAndSlowlyChangeScaleComponent->SetModelScale(scale);

	normalModelId = Renderer::GetInstance()->LoadModel("Resouce/model/ball.mv1");
	modelAndSlowlyChangeScaleComponent->SetModel(normalModelId);
	modelAndSlowlyChangeScaleComponent->SetModelScale(scale);

	MovePlayerComponent * movePlayerComponent;
	movePlayerComponent = new MovePlayerComponent(this, ModelComponent::DrawPlayerNumber, moveKey, next, VGet(5.0f, 0, 0));

	sphereCollider = new SphereColliderComponent(this, 150, 0.01f);

	countDownComponent = new CountDownComponent(superCountMax);
	superLikelyCountDownComponent = new CountDownComponent(superEndCount);
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
	if (superLikelyCountDownComponent->CountEnd())
	{
		LikelyChangeNormalModel();
	}
}

void Player::OnCollision()
{
	ChangeSuperModel();
}

void Player::LikelyChangeNormalModel()
{
	modelAndSlowlyChangeScaleComponent->StartCoroutine(normalModelScale, 10);
}

void Player::ChangeNormalModel()
{
	//���f����ύX
	modelAndSlowlyChangeScaleComponent->SetModel(normalModelId);

	//�^�O��ύX
	sphereCollider->TagChange(SphereColliderComponent::CollisionTag::NormalPlayer);
}

void Player::ChangeSuperModel()
{
	//���f����ύX
	modelAndSlowlyChangeScaleComponent->SetModel(superModelId);

	modelAndSlowlyChangeScaleComponent->StartCoroutine(superModelScale, 10);

	//�^�O��ύX
	sphereCollider->TagChange(SphereColliderComponent::CollisionTag::SuperPlayer);

	countDownComponent->ResetCount();
	superLikelyCountDownComponent->ResetCount();
}

