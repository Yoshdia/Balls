#include "DxLib.h"
#include "AddPointWall.h"

AddPointWall::AddPointWall(VECTOR initPos)
	:Wall(initPos, BoxColliderComponent::ColliderTag::AddPointWall)
{
}

AddPointWall::~AddPointWall()
{
}

void AddPointWall::OnCollision()
{
	SetState(Actor::ActiveState::Paused);
	ClearWall();
}
