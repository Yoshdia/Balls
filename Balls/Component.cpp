#include "Component.h"
#include "Actor.h"

// コンポーネント通し番号
int Component::mNo = 10000;
///////////////////////////////////////////////////////////
// Component システムコンストラクタ
// 所有者のActorクラスに自分自身のコンポーネントを追加
///////////////////////////////////////////////////////////
Component::Component(Actor* owner, int updateOrder)
	:mOwner(owner)
	, mUpdateOrder(updateOrder)
	, mCreateIndex(mNo)
{
	//所有Actorにこのコンポーネントを追加する
	mOwner->AddComponent(this);
	mNo++;
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

// コンポーネントの毎フレームupdate処理 必要あればオーバーライド
void Component::Update(float deltaTime)
{

}