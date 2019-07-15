#include "GameSpeedManager.h"

GameSpeedManager* GameSpeedManager::gameSpeedManager = nullptr;
const float GameSpeedManager::PlusSpeed= 0.05f;

GameSpeedManager::GameSpeedManager()
{
	ResetGameSpeed();
}

void GameSpeedManager::Create()
{
	if (!gameSpeedManager)
	{
		gameSpeedManager = new GameSpeedManager;
	}
}

void GameSpeedManager::Delete()
{
	delete gameSpeedManager;
	gameSpeedManager = nullptr;
}
