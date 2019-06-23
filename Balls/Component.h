#pragma once
#include "Game.h"

class Actor;

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual     ~Component();
	virtual void Update(float deltaTime);                              // コンポーネントをdeltaTimeで更新
	int          getUpdateOrder() const { return mUpdateOrder; }       // 更新順序を取得

protected:
	class Actor* mOwner;            // 所有アクター
	int          mUpdateOrder;      // 更新順序
	int          mCreateIndex;      // 作成通し番号
	static int   mNo;               // コンポーネント作成カウンタ
};