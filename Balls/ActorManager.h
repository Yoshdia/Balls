#pragma once
#include <vector>

class Actor;

//Actor���ׂĂ��������X�V�A�폜����V���O���g���N���X
class ActorManager
{
public:
	static ActorManager* GetInstance() { return actorManager; }

	//ActorManager�V���O���g���̐����Ɖ���֐�
	static void Create();
	static void Delete();

	//Actor�̍X�V�@pending����upDate�ւ̈ڍs���s��
	void ActorUpdate(float deltaTime);
	void AddActor(Actor *actor);
	void RemoveActor(Actor *actor);
	void ShutDown();
private:
	ActorManager() {};
	static ActorManager *actorManager;
	//�X�V����Actor
	std::vector<class Actor*> upDateActors;
	//�ۗ�����Actor
	std::vector<class Actor*> pendingActors;
};

