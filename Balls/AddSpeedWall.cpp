#include "DxLib.h"
#include "MoveComponent.h"
#include "AddSpeedWall.h"
#include "GameSpeedManager.h"

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
	ClearWall();
}