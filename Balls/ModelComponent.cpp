#include "DxLib.h"
#include "ModelComponent.h"
#include "Actor.h"
#include "Game.h"

ModelComponent::ModelComponent(Actor * owner, int setProcessNumber)
	:Component(owner,setProcessNumber)
	, modelId(-1)
{
	Game::GetInstance()->AddModel(this);
}

ModelComponent::~ModelComponent()
{
	Game::GetInstance()->RemoveModel(this);
}

void ModelComponent::SetModelScale(float scale)
{
	MV1SetScale(modelId, VGet(scale, scale, scale));
}

void ModelComponent::DrawModel()
{
	//Š—LActor‚ªŠŽ‚µ‚Ä‚éî•ñ‚ð‚à‚Æ‚ÉModel‚ð•\Ž¦‚·‚é
	const VECTOR position=ownerActor->GetPosition();
	float scale = ownerActor->GetScale();
	VECTOR rotation= ownerActor->GetRotation();

	if (modelId != -1)
	{
		MV1SetPosition(modelId, position);
		MV1SetRotationXYZ(modelId, rotation);
		MV1DrawModel(modelId);
	}
}

void ModelComponent::SetModel(int model)
{
	if (model == -1)
	{
		return;
	}
	modelId = model;
}
