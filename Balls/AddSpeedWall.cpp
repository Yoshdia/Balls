#include "DxLib.h"
#include "MoveComponent.h"
#include "AddSpeedWall.h"
#include "GameSpeedManager.h"
#include "EffectFactory.h"

AddSpeedWall::AddSpeedWall()
	:Wall(BoxColliderComponent::ColliderTag::AddSpeedWall, "Resouce/model/addSpeedWall.mv1")
{
}


AddSpeedWall::~AddSpeedWall()
{
}


void AddSpeedWall::OnCollision()
{
	GameSpeedManager::GetInstance()->AddGameSpeed();
	EffectFactory::GetInstance()->PopEffect(VGet(0, 0, 30), EffectFactory::Effects::Line);
	ClearWall();
}