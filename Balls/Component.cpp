#include "Component.h"
#include "Actor.h"

// �R���|�[�l���g�ʂ��ԍ�
int Component::componentCount = 0;
///////////////////////////////////////////////////////////
// Component �V�X�e���R���X�g���N�^
// ���L�҂�Actor�N���X�Ɏ������g�̃R���|�[�l���g��ǉ�
///////////////////////////////////////////////////////////
Component::Component(Actor* owner, int setProcessNumber)
	:ownerActor(owner)
	, processNumber(setProcessNumber)
{
	//���LActor�ɂ��̃R���|�[�l���g��ǉ�����
	ownerActor->AddComponent(this);
	componentCount++;
}

Component::~Component()
{
	ownerActor->RemoveComponent(this);
}

// �R���|�[�l���g�̖��t���[��update���� �K�v����΃I�[�o�[���C�h
void Component::Update(float deltaTime)
{

}