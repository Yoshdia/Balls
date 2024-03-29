#include "Player.h"
#include <math.h>
#include "ModelComponent.h"
#include "MovePlayerComponent.h"
#include "Renderer.h"
#include "SphereColliderComponent.h"
#include "CountDownComponent.h" 
#include "SlowlyChangeScaleComponent.h"
#include "HeadForTargetComponent.h"

const VECTOR Player::normalModelScale = VGet(0.01f, 0.01f, 0.01f);
//const VECTOR Player::normalModelScale = VGet(10, 10, 10);
const VECTOR Player::superModelScale = VGet(0.02f, 0.02f, 0.02f);
//const VECTOR Player::superModelScale = VGet(10, 10, 10);

const int Player::superCountMax=460;
const int Player::superEndLikeryCount=100;
const float Player::superEndCount= Player::superCountMax- (Player::superEndLikeryCount*1.5f);
const VECTOR Player::MoveSpeed = VGet(5.0f, 0, 0);

Player::Player(VECTOR initPos, Game::MoveDirection next, char moveKey)
{
	position = initPos;
	firstPosition=initPos;
	firstDirection = next;

	scale = VGet(0.01f, 0.01f, 0.01f);
	//モデルを保存し描画するComponentを実装(後々使用するsuperBallのモデルもここでScaleをSetしておく)
	//modelComponent = new ModelComponent(this,ModelComponent::DrawPlayerNumber);
	modelAndSlowlyChangeScaleComponent = new SlowlyChangeScaleComponent(this, 200);

	superModelId = Renderer::GetInstance()->LoadModel("Resouce/model/superBall.mv1");
	modelAndSlowlyChangeScaleComponent->SetModel(superModelId);
	modelAndSlowlyChangeScaleComponent->SetModelScale(scale);

	normalModelId = Renderer::GetInstance()->LoadModel("Resouce/model/ball.mv1");
	modelAndSlowlyChangeScaleComponent->SetModel(normalModelId);
	modelAndSlowlyChangeScaleComponent->SetModelScale(scale);

	movePlayerComponent = new MovePlayerComponent(this, ModelComponent::DrawPlayerNumber, moveKey, next, MoveSpeed);

	sphereCollider = new SphereColliderComponent(this, 150, 0.01f);

	countDownComponent = new CountDownComponent(superCountMax);
	superLikelyCountDownComponent = new CountDownComponent(superEndCount);

	headForFirstPosition = new HeadForTargetComponent(this, 200, VGet(0, 0, 0), VGet(0, 0, 0));
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

void Player::StartMove()
{
	movePlayerComponent->StartCorutine();
}

void Player::StopMove()
{
	movePlayerComponent->StopCorutine();
}

void Player::SetFirstPosition()
{
	headForFirstPosition->SetMoveSpeed(VGet(1, 5, 0));
	headForFirstPosition->SetTargetPos(firstPosition);
}

void Player::MoveFirstPosition(float deltaTime)
{
	headForFirstPosition->HeadForTarget(deltaTime);
}

void Player::SkipMoveFirstPosition()
{
	headForFirstPosition->SetMoveSpeed(VGet(0, 0, 0));
	movePlayerComponent->SetMoveDirection(firstDirection);
	SetPosition(firstPosition);
}

void Player::LikelyChangeNormalModel()
{
	modelAndSlowlyChangeScaleComponent->StartCoroutine(normalModelScale, 10);
}

void Player::ChangeNormalModel()
{
	//モデルを変更
	modelAndSlowlyChangeScaleComponent->SetModel(normalModelId);

	//タグを変更
	sphereCollider->TagChange(SphereColliderComponent::CollisionTag::NormalPlayer);
}

void Player::ChangeSuperModel()
{
	//モデルを変更
	modelAndSlowlyChangeScaleComponent->SetModel(superModelId);

	modelAndSlowlyChangeScaleComponent->StartCoroutine(superModelScale, 10);

	//タグを変更
	sphereCollider->TagChange(SphereColliderComponent::CollisionTag::SuperPlayer);

	countDownComponent->ResetCount();
	superLikelyCountDownComponent->ResetCount();
}

