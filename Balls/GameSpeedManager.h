#pragma once

//gameSpeedを管理するシングルトンクラス
class GameSpeedManager
{
public:
	static GameSpeedManager* GetInstance() { return gameSpeedManager; }
	void Create();
	void Delete();
	~GameSpeedManager() {};

	float GetGameSpeed() { return gameSpeed; }
	void AddGameSpeed() { gameSpeed += PlusSpeed; }
	void ResetGameSpeed() { gameSpeed = 1.0f; }
private:
	GameSpeedManager();
	static GameSpeedManager* gameSpeedManager;

	float gameSpeed;
	static const float PlusSpeed;
};

