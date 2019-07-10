#include "JammerWall.h"
#include "BoxColliderComponent.h"

JammerWall::JammerWall()
	:Wall(BoxColliderComponent::ColliderTag::JammerWall, "Resouce/model/wall.mv1")
{
}

JammerWall::~JammerWall()
{
}
