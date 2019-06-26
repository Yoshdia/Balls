#pragma once
#include "Game.h"

class Actor;

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void Update(float deltaTime);                              // コンポーネントをdeltaTimeで更新
	// 更新順序を返す
	int getProccesNumber() const { return processNumber; } //getUpdateOrder
protected:
	//このComponentを所有しているActorへのアドレス
	class Actor* ownerActor;//owner
	// 更新順序
	int processNumber;//mUpdateOrder
	//int mCreateIndex;      // 作成通し番号
	// コンポーネントが作成されると増えるカウント
	static int componentCount;//mNo
};