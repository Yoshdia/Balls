#include "DxLib.h"
#include "MoveComponent.h"
#include "AddSpeedWall.h"
#include "Game.h"

AddSpeedWall::AddSpeedWall()
	:Wall(BoxColliderComponent::ColliderTag::AddSpeedWall, "Resouce/model/addSpeedWall.mv1")
{
}


AddSpeedWall::~AddSpeedWall()
{
}


void AddSpeedWall::OnCollision()
{
	//Game::GetInstance()->AddGameSpeed();
	ClearWall();
}