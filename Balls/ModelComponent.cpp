#include "DxLib.h"
#include "ModelComponent.h"
#include "Actor.h"
#include "Game.h"

ModelComponent::ModelComponent(Actor * owner, int drawOrder)
	:Component(owner)
	, mModelID(-1)
	, mDrawOrder(drawOrder)
{
	//Game::GetInstance()->AddSprite(this);
}

ModelComponent::~ModelComponent()
{
	//Game::GetInstance()->RemoveSprite(this);
}

void ModelComponent::Draw()
{
	VECTOR vec;
	float scale;
	VECTOR rotation;
	vec = mOwner->GetPosition();
	scale = mOwner->GetScale();
	rotation = mOwner->GetRotation();

	if (mModelID != -1)
	{
		MV1SetPosition(mModelID, vec);
		MV1SetRotationXYZ(mModelID, rotation);
		MV1DrawModel(mModelID);
	}

}

void ModelComponent::SetModel(int modelID)
{
	if (modelID == -1)
	{
		return;
	}
	mModelID = modelID;
}
