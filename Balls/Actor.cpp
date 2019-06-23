#include "Game.h"
#include "Actor.h"
#include "Component.h"
#include <algorithm>

int Actor::mNo = 0;

Actor::Actor()
	:mState(EActive)
	, mPosition(VGet(0,0,0))
	, mScale(1.0f)
	, mRotation(VGet(0,0,0))
	, mIndex(mNo)
{
	Game::GetInstance()->AddActor(this);
	mNo++;
}

Actor::~Actor()
{
	Game::GetInstance()->RemoveActor(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == EActive)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(Component* component)
{
	//�\�[�g���ꂽvector���̑}���_��������
	//(�l���������������ŏ��̗v�f��������)
	int myOrder = component->getUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter)
	{
		if (myOrder < (*iter)->getUpdateOrder())
		{
			break;
		}
	}
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}

//Vector2 Actor::GetForward() const
//{
//	return Vector2(Math::Cos(mRotation), Math::Sin(mRotation));
//}
