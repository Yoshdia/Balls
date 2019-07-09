#include "SuperWall.h"

SuperWall::SuperWall(VECTOR initPos)
	:Wall(initPos,BoxColliderComponent::ColliderTag::SuperWall)
{
}

SuperWall::~SuperWall()
{
}
