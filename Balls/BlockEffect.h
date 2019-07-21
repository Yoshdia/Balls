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
	//�����n�_���牝���n�_�܂ł̋���
	static const float RoundDistance;
	//��������
	int lifeCnt;
	static const int LifeCntMax;
	CountDownComponent* countDownComponent;
	MoveComponent* moveComponent;


};

