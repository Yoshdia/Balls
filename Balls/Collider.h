#pragma once

#include <vector>

class SphereColliderComponent;
class BoxColliderComponent;
class Score;

//Sphere(player)やBox(wall)を所持し衝突判定まで行うシングルトンクラス
class Collider
{
public:
	static Collider* GetInstance() { return collider; }

	//Colliderシングルトンの生成と解放関数
	static void Create();
	static void Delete();

	void AddBoxCollider(BoxColliderComponent* box);
	void RemoveCollider(BoxColliderComponent* box);
	void AddSphereCollider(SphereColliderComponent* sphere);
	void RemoveSphereCollider(SphereColliderComponent* sphere);

	//衝突判定を行う関数を呼ぶ関数。戻り値は同じ　Playから呼ばれる
	bool CollisionCall(Score* score);
	//衝突判定を行う関数
	bool CollisionBallWall(SphereColliderComponent * sphere, BoxColliderComponent * box);

	void ShutDown();
private:
	Collider() {};
	static Collider* collider;

	//球(Player)と壁(wall)を格納しているVector
	std::vector<SphereColliderComponent*> sphereCollider;
	std::vector<BoxColliderComponent*> boxCollider;
};

