#include "Component.h"
#include "Actor.h"

// �R���|�[�l���g�ʂ��ԍ�
int Component::mNo = 10000;
///////////////////////////////////////////////////////////
// Component �V�X�e���R���X�g���N�^
// ���L�҂�Actor�N���X�Ɏ������g�̃R���|�[�l���g��ǉ�
///////////////////////////////////////////////////////////
Component::Component(Actor* owner, int updateOrder)
	:mOwner(owner)
	, mUpdateOrder(updateOrder)
	, mCreateIndex(mNo)
{
	//���LActor�ɂ��̃R���|�[�l���g��ǉ�����
	mOwner->AddComponent(this);
	mNo++;
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

// �R���|�[�l���g�̖��t���[��update���� �K�v����΃I�[�o�[���C�h
void Component::Update(float deltaTime)
{

}