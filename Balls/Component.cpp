#include "Component.h"
#include "Actor.h"

// コンポーネント通し番号
int Component::componentCount = 0;
///////////////////////////////////////////////////////////
// Component システムコンストラクタ
// 所有者のActorクラスに自分自身のコンポーネントを追加
///////////////////////////////////////////////////////////
Component::Component(Actor* owner, int setProcessNumber)
	:ownerActor(owner)
	, processNumber(setProcessNumber)
{
	//所有Actorにこのコンポーネントを追加する
	ownerActor->AddComponent(this);
	componentCount++;
}

Component::~Component()
{
	ownerActor->RemoveComponent(this);
}

// コンポーネントの毎フレームupdate処理 必要あればオーバーライド
void Component::Update(float deltaTime)
{

}