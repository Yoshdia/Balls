#include "JammerWall.h"
#include "BoxColliderComponent.h"
#include "EffectFactory.h"


JammerWall::JammerWall()
	:Wall(BoxColliderComponent::ColliderTag::JammerWall, "Resouce/model/wall.mv1")
{
}

JammerWall::~JammerWall()
{
}

void JammerWall::OnCollision()
{
	EffectFactory::GetInstance()->PopEffect(GetPosition(), EffectFactory::Effects::Block);
	ClearWall();
}
