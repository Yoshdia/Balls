#include "DxLib.h"
#include "MoveComponent.h"
#include "AddSpeedWall.h"
#include "Game.h"

AddSpeedWall::AddSpeedWall(VECTOR initPos)
	:Wall(initPos, BoxColliderComponent::ColliderTag::AddSpeedWall)
{
}


AddSpeedWall::~AddSpeedWall()
{
}


void AddSpeedWall::OnCollision()
{
	Game::GetInstance()->AddGameSpeed();
}