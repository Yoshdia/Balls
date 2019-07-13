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
	//actor��upDateingActors��pendingActors�̒�����폜����
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
	//upDateActors�̍폜
	while (!upDateActors.empty())
	{
		delete upDateActors.back();
	}
	upDateActors.clear();

	//pendingActors�̍폜
	while (!pendingActors.empty())
	{
		delete pendingActors.back();
	}
	pendingActors.clear();
}

void ActorManager::ActorUpdate(float deltaTime)
{
	//�S�Ă�Actor�̍X�V����
	for (auto actor : upDateActors)
	{
		actor->Update(deltaTime);
	}
	//����F���ōX�V���ׂ�Actor�̏������S�ďI��������actor�ɑ}������
	for (auto actor : pendingActors)
	{
		upDateActors.emplace_back(actor);
	}
	pendingActors.clear();
}
