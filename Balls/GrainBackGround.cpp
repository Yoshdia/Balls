#include "GrainBackGround.h"
#include "HeadForTargetComponent.h"
#include "ModelComponent.h"
#include "Renderer.h"
#include <math.h>

//// 正規化(ベクトルの長さを1にする)
//void normalize(float& x, float& y, float& z)
//{
//	float mag = 1 / (sqrt(x*x + y * y + z * z));
//	x *= mag;
//	y *= mag;
//	z *= mag;
//}

const VECTOR GrainBackGround::MoveSpeed = VGet(1.0f, 0.0f, 5.0f);

GrainBackGround::GrainBackGround()
{
	headForTarget = new HeadForTargetComponent(this, 120, VGet(0, 0, 0), VGet(0, 0, 0));

	scale = VGet(0.001f, 0.001f, 0.001f);
	SetState(Actor::ActiveState::Paused);
	moving = false;

	modelComponent = new ModelComponent(this, ModelComponent::DrawGrainNumber);
	redModel = Renderer::GetInstance()->LoadModel("Resouce/model/normalRedSphere.mv1");
	modelComponent->SetModel(redModel);
	modelComponent->SetModelScale(scale);

	whiteModel = Renderer::GetInstance()->LoadModel("Resouce/model/normalSphere.mv1");
	modelComponent->SetModel(whiteModel);
	modelComponent->SetModelScale(scale);

}

GrainBackGround::~GrainBackGround()
{
}

void GrainBackGround::ResetBackGround(VECTOR pos, VECTOR target)
{
	SetPosition(pos);
	headForTarget->SetTargetPos(target);
	SetState(Actor::ActiveState::Active);
	//moveComponent->SetMoveSpeed(CalculateVelocity(pos, target));
	//offset = pos;
	//this->target = VSub(target, pos);
	//b = tan(30 * (360 / (3.14f * 2)));
	//a = (target.y - b * target.x) / -(target.x * target.x);
	//ab = 0;
	scale = VGet(1, 1, 1)*(GetRand(10)*0.001f);
	moving = true;
}

void GrainBackGround::UpdateActor(float deltaTime)
{
	if (moving)
	{
		headForTarget->SetMoveSpeed(MoveSpeed);
		headForTarget->HeadForTarget(deltaTime);
	}

	if (position.z < -10)
	{
		SetState(Actor::ActiveState::Paused);
	}
}

void GrainBackGround::StopMove()
{
	moving = false;
	headForTarget->MoveComponent::SetMoveSpeed(VGet(0, 0, 0));
}

void GrainBackGround::MoveReStart()
{
	moving = true;
}

void GrainBackGround::ColorChange(GrainColor color)
{
	switch (color)
	{
	case(GrainColor::Red):modelComponent->SetModel(redModel); break;
	case(GrainColor::white):modelComponent->SetModel(whiteModel); break;
	}
}

//VECTOR GrainBackGround::CalculateVelocity(const VECTOR& pointA,const VECTOR& pointB)
//{
//	// 射出角をラジアンに変換
//	float rad = 30 *3.14f/ 180;
//	//float rad = angle * Mathf.PI / 180;
//
//	// 水平方向の距離x
//	float x = pointB.x - pointA.x;
//	//float x = Vector2.Distance(new Vector2(pointA.x, pointA.z), new Vector2(pointB.x, pointB.z));
//
//	// 垂直方向の距離y
//	float y = pointB.y - pointA.y;
//
//	// 斜方投射の公式を初速度について解く
//	float speed = sqrt( (x*x) / (2 *(cos(rad)*cos(rad)) * (x * tan(rad) + y)));
//	//float speed = Mathf.Sqrt(-Physics.gravity.y * Mathf.Pow(x, 2) / (2 * Mathf.Pow(Mathf.Cos(rad), 2) * (x * Mathf.Tan(rad) + y)));
//
//	VECTOR vec = VGet(pointB.x - pointA.x, x * tan(rad), pointB.z - pointA.z);
//
//	normalize(vec.x, vec.y, vec.z);
//
//	return vec* speed;
//	//return (new Vector3(pointB.x - pointA.x, x * Mathf.Tan(rad), pointB.z - pointA.z).normalized * speed);
//
//}

//VECTOR GrainBackGround::Determine()
//{
//	if (ab <= target.x)
//	{
//		float y = a * ab * ab + b * ab;
//		ab += 0.3f;
// 		return VGet(ab, y, 0);
//	}
//}
