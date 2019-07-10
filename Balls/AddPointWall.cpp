#include "DxLib.h"
#include "AddPointWall.h"

AddPointWall::AddPointWall()
	:Wall( BoxColliderComponent::ColliderTag::AddPointWall, "Resouce/model/plusWall.mv1")
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
