#pragma once
#include "Actor.h"
class CountDownComponent;
class MoveComponent;

class BlockEffect :
	public Actor
{
public:
enum BlockMoveDirection
{
	LeftUp,
	RightUp,
	LeftDown,
	RightDown,
};
	BlockEffect();
	~BlockEffect();
	void UpdateActor(float deltaTime);
	void ResetBlock(VECTOR setMiddlePos, BlockMoveDirection dir);
private:
	//初期地点から往復地点までの距離
	static const float RoundDistance;
	//生存時間
	int lifeCnt;
	static const int LifeCntMax;
	CountDownComponent* countDownComponent;
	MoveComponent* moveComponent;


};

