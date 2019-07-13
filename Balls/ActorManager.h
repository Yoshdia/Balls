#pragma once
#include <vector>

class Actor;

//Actorすべてを所持し更新、削除するシングルトンクラス
class ActorManager
{
public:
	static ActorManager* GetInstance() { return actorManager; }

	//ActorManagerシングルトンの生成と解放関数
	static void Create();
	static void Delete();

	//Actorの更新　pendingからupDateへの移行も行う
	void ActorUpdate(float deltaTime);
	void AddActor(Actor *actor);
	void RemoveActor(Actor *actor);
	void ShutDown();
private:
	ActorManager() {};
	static ActorManager *actorManager;
	//更新中のActor
	std::vector<class Actor*> upDateActors;
	//保留中のActor
	std::vector<class Actor*> pendingActors;
};

