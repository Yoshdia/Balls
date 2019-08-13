#pragma once

#include <vector>

class SphereColliderComponent;
class BoxColliderComponent;
class Score;

//Sphere(player)��Box(wall)���������Փ˔���܂ōs���V���O���g���N���X
class Collider
{
public:
	static Collider* GetInstance() { return collider; }

	//Collider�V���O���g���̐����Ɖ���֐�
	static void Create();
	static void Delete();

	void AddBoxCollider(BoxColliderComponent* box);
	void RemoveCollider(BoxColliderComponent* box);
	void AddSphereCollider(SphereColliderComponent* sphere);
	void RemoveSphereCollider(SphereColliderComponent* sphere);

	//�Փ˔�����s���֐����ĂԊ֐��B�߂�l�͓����@Play����Ă΂��
	bool CollisionCall(Score* score);
	//�Փ˔�����s���֐�
	bool CollisionBallWall(SphereColliderComponent * sphere, BoxColliderComponent * box);

	void ShutDown();
private:
	Collider() {};
	static Collider* collider;

	//��(Player)�ƕ�(wall)���i�[���Ă���Vector
	std::vector<SphereColliderComponent*> sphereCollider;
	std::vector<BoxColliderComponent*> boxCollider;
};

