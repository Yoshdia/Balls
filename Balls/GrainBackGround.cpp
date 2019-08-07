#include "GrainBackGround.h"
#include "MoveComponent.h"
#include "ModelComponent.h"
#include <math.h>

//// 正規化(ベクトルの長さを1にする)
//void normalize(float& x, float& y, float& z)
//{
//	float mag = 1 / (sqrt(x*x + y * y + z * z));
//	x *= mag;
//	y *= mag;
//	z *= mag;
//}

GrainBackGround::GrainBackGround()
{
	moveComponent = new MoveComponent(this, 120, VGet(0, 0, 0), VGet(0, 0, 0));

	scale = VGet(0.001f, 0.001f, 0.001f);
	ModelComponent* modelComponent;
	modelComponent = new ModelComponent(this, 150, scale, "Resouce/model/normalSphere.mv1");
	SetState(Actor::ActiveState::Paused);
	moving = false;
}

GrainBackGround::~GrainBackGround()
{
}

void GrainBackGround::ResetBackGround(VECTOR pos, VECTOR target)
{
	SetPosition(pos);
	targetPos = target;
	z = 0;
	SetState(Actor::ActiveState::Active);
	//moveComponent->SetMoveSpeed(CalculateVelocity(pos, target));
	//offset = pos;
	//this->target = VSub(target, pos);
	//b = tan(30 * (360 / (3.14f * 2)));
	//a = (target.y - b * target.x) / -(target.x * target.x);
	//ab = 0;
	scale = VGet(1,1,1)*(GetRand(10)*0.001f);
	moving = true;
}

void GrainBackGround::UpdateActor(float deltaTime)
{
	if (moving)
	{
	SetY();
	moveComponent->SetMoveSpeed(VGet(SetX()*1, 0, z*5));
	}

	if (position.z < -10)
	{
		SetState(Actor::ActiveState::Paused);
	}
}

void GrainBackGround::StopMove()
{
	moving = false;
	moveComponent->SetMoveSpeed(VGet(0, 0, 0));
}

void GrainBackGround::MoveReStart()
{
	moving = true;
}

float GrainBackGround::SetX()
{
	bool right = position.x < targetPos.x ? true : false;
	float x = 0;

	if (right)
	{
		if (targetPos.x > position.x)
		{
			x= 1;
		}
	}
	else
	{
		if (targetPos.x < position.x)
		{
			x= -1;
		}
	}
	return x;
}

void GrainBackGround::SetY()
{
	bool up = position.z < targetPos.z ? true : false;

	if (up)
	{
		if (targetPos.z > position.z)
		{
			z += 0.01f;
		}
		else
		{
			z = 0;
		}
	}
	else
	{
		if (targetPos.z < position.z)
		{
			z -= 0.01f;
		}
		else
		{
			z = 0;
		}
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
