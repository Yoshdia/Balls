#include "ActorManager.h"
#include "Actor.h"

ActorManager *ActorManager::actorManager = nullptr;

void ActorManager::Create()
{
	if (!actorManager)
	{
		actorManager = new ActorManager;
	}
}

void ActorManager::Delete()
{
	delete actorManager;
	actorManager = nullptr;
}

void ActorManager::AddActor(Actor * actor)
{
	pendingActors.emplace_back(actor);
}

void ActorManager::RemoveActor(Actor * actor)
{
	//actorをupDateingActorsとpendingActorsの中から削除する
	auto iter = std::find(pendingActors.begin(), pendingActors.end(), actor);
	if (iter != pendingActors.end())
	{
		std::iter_swap(iter, pendingActors.end() - 1);
		pendingActors.pop_back();
		return;
	}
	iter = std::find(upDateActors.begin(), upDateActors.end(), actor);
	if (iter != upDateActors.end())
	{
		std::iter_swap(iter, upDateActors.end() - 1);
		upDateActors.pop_back();
		return;
	}
}

void ActorManager::ShutDown()
{
	//upDateActorsの削除
	while (!upDateActors.empty())
	{
		delete upDateActors.back();
	}
	upDateActors.clear();

	//pendingActorsの削除
	while (!pendingActors.empty())
	{
		delete pendingActors.back();
	}
	pendingActors.clear();
}

void ActorManager::ActorUpdate(float deltaTime)
{
	//全てのActorの更新処理
	for (auto actor : upDateActors)
	{
		actor->Update(deltaTime);
	}
	//このF中で更新すべきActorの処理が全て終わった後にactorに挿入する
	for (auto actor : pendingActors)
	{
		upDateActors.emplace_back(actor);
	}
	pendingActors.clear();
}
