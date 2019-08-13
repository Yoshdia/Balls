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
			//�ǂ̏Փˏ����t���O�������Ă��Ȃ��ꍇ�����ŏI������
			if (!box->GetIsCollision())
			{
				continue;
			}
			bool end = CollisionBallWall(ball, box);
			
			if (end)
			{
				BoxColliderComponent::ColliderTag boxTag = box->GetTag();
				//�����ǂ������ꍇ�AgameSpeed������������
				if (boxTag == BoxColliderComponent::ColliderTag::AddSpeedWall)
				{
					box->OnCollision();
					
					continue;
				}
				//addPointWall�������ꍇ�A�X�R�A�����Z����
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
				//Player��������Ԃ������ꍇ�A�ǂ�Pause�ɂ���
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
	//���W�┼�a�A��Ђ̒����Ȃǂ����ꂼ��擾
	SphereInfo sphereInfo = sphere->GetInfo();
	BoxInfo boxInfo = box->GetIndo();

	//�������W�ɂ��邩
	if ((int)boxInfo.position.x == (int)sphereInfo.position.x)
	{
		return true;
	}

	//�~���a�ׂ̂���
	float sphereLengh = sphereInfo.length*sphereInfo.length;
	sphereLengh = 1;
	boxInfo.length = 1;
	
	//box�̍�����W���~�͈̔͂ɓ����Ă��邩
	VECTOR boxLeftUp = VGet(boxInfo.position.x - boxInfo.length, boxInfo.position.y + boxInfo.length, 0);
	if (((boxLeftUp.x - sphereInfo.position.x)*(boxLeftUp.x - sphereInfo.position.x)) +
		((boxLeftUp.y - sphereInfo.position.y)*(boxLeftUp.y - sphereInfo.position.y)) <= sphereLengh)
	{
		return true;
	}

	//box�̉E�����W���~�͈̔͂ɓ����Ă��邩
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
