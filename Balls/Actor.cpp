#include "ActorManager.h"
#include "Actor.h"
#include "Component.h"
#include <algorithm>

//指定が無かった場合0にする
int Actor::actorNumber = 0;

Actor::Actor()
	:state(ActiveState::Active)
	, position(OriginPos)
	, scale(OriginScale)
	, rotation(OriginQua)
{
	ActorManager::GetInstance()->AddActor(this);
	actorNumber++;
}

Actor::~Actor()
{
	ActorManager::GetInstance()->RemoveActor(this);
	while (!myComponents.empty())
	{
		delete myComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (state == ActiveState::Active)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : myComponents)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(Component* component)
{
	//そのComponentの更新順序を取得し、その順序より大きい値を見つけたらその前に挿入する
	int componentNumber = component->getProccesNumber();
	auto iter = myComponents.begin();
	for (;iter != myComponents.end(); ++iter)
	{
		int iterComponentNumber = (*iter)->getProccesNumber();
		if (componentNumber < iterComponentNumber||
			componentNumber == iterComponentNumber)
		{
			break;
		}
	}
	myComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	//myComponentsからcomponentを削除する
	auto iter = std::find(myComponents.begin(), myComponents.end(), component);
	if (iter != myComponents.end())
	{
		myComponents.erase(iter);
	}
}

//Vector2 Actor::GetForward() const
//{
//	return Vector2(Math::Cos(mRotation), Math::Sin(mRotation));
//}
