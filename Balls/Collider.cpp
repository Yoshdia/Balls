#include "Collider.h"
#include "SphereColliderComponent.h"
#include "BoxColliderComponent.h"

Collider* Collider::collider = nullptr;

void Collider::Create()
{
	if (!collider)
	{
		collider = new Collider;
	}
}

void Collider::Delete()
{
	delete collider;
	collider = nullptr;
}

void Collider::AddBoxCollider(BoxColliderComponent * box)
{
	boxCollider.emplace_back(box);
}

void Collider::RemoveCollider(BoxColliderComponent * box)
{
	auto iter = std::find(boxCollider.begin(), boxCollider.end(), box);
	if (iter != boxCollider.end())
	{
		std::iter_swap(iter, boxCollider.end() - 1);
		boxCollider.pop_back();
	}
}

void Collider::AddSphereCollider(SphereColliderComponent * sphere)
{
	sphereCollider.emplace_back(sphere);
}

void Collider::RemoveSphereCollider(SphereColliderComponent * sphere)
{
	auto iter = std::find(sphereCollider.begin(), sphereCollider.end(), sphere);
	if (iter != sphereCollider.end())
	{
		std::iter_swap(iter, sphereCollider.end() - 1);
		sphereCollider.pop_back();
	}
}

bool Collider::CollisionCall()
{
	for (auto ball : sphereCollider)
	{
		for (auto box : boxCollider)
		{
			//壁の衝突準備フラグが立っていない場合ここで終了する
			if (!box->GetIsCollision())
			{
				continue;
			}
			bool end = CollisionBallWall(ball, box);
			
			if (end)
			{
				BoxColliderComponent::ColliderTag boxTag = box->GetTag();
				//加速壁だった場合、gameSpeedを加速させる
				if (boxTag == BoxColliderComponent::ColliderTag::AddSpeedWall)
				{
					box->OnCollision();
					
					continue;
				}
				//addPointWallだった場合、スコアを加算する
				if (boxTag == BoxColliderComponent::ColliderTag::AddPointWall)
				{
					box->OnCollision();

					continue;
				}
				if (boxTag == BoxColliderComponent::ColliderTag::SuperWall)
				{
					box->OnCollision();
					ball->OnCollision();
					
					continue;
				}
				//Playerが強化状態だった場合、壁をPauseにする
				if (ball->GetTag() == SphereColliderComponent::CollisionTag::SuperPlayer)
				{
					box->OnCollision();
					continue;
				}
				ball->OutOfScreen();
				return end;
			}
		}
	}
	return false;
}

bool Collider::CollisionBallWall(SphereColliderComponent * sphere, BoxColliderComponent * box)
{
	//座標や半径、一片の長さなどをそれぞれ取得
	SphereInfo sphereInfo = sphere->GetInfo();
	BoxInfo boxInfo = box->GetIndo();

	//同じ座標にいるか
	if ((int)boxInfo.position.x == (int)sphereInfo.position.x)
	{
		return true;
	}

	//円半径のべき乗
	float sphereLengh = sphereInfo.length*sphereInfo.length;
	sphereLengh = 1;
	boxInfo.length = 1;
	
	//boxの左上座標が円の範囲に入っているか
	VECTOR boxLeftUp = VGet(boxInfo.position.x - boxInfo.length, boxInfo.position.y + boxInfo.length, 0);
	if (((boxLeftUp.x - sphereInfo.position.x)*(boxLeftUp.x - sphereInfo.position.x)) +
		((boxLeftUp.y - sphereInfo.position.y)*(boxLeftUp.y - sphereInfo.position.y)) <= sphereLengh)
	{
		return true;
	}

	//boxの右下座標が円の範囲に入っているか
	VECTOR boxRightDown = VGet(boxInfo.position.x + boxInfo.length, boxInfo.position.y - boxInfo.length, 0);
	{
		if (((boxRightDown.x - sphereInfo.position.x)*(boxRightDown.x - sphereInfo.position.x)) +
			((boxRightDown.y - sphereInfo.position.y)*(boxRightDown.y - sphereInfo.position.y)) <= sphereLengh)
		{
			return true;
		}
	}
	return false;
}

void Collider::ShutDown()
{
}
