//#include <iostream>
#include "DxLib.h"
#include "Scene.h"
#include "Player.h"
#include "Title.h"
#include "Play.h"
#include "Clear.h"
#include "Wall.h"
#include "Actor.h"
#include "ModelComponent.h"
#include "Ground.h"
#include "SphereColliderComponent.h"
#include "BoxColliderComponent.h"
#include "MoveComponent.h"
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib") 

Game *Game::game = NULL;


void Game::Create()
{
	if (!game)
	{
		game = new Game;
	}
}

void Game::Delete()
{
	delete game;
	game = NULL;
}

void Game::MainProcess()
{
	//Dxlib����������
	if (DxLib_Init() == -1)
	{
		return;
	}
	//�X�N���[�����[�h�̕ύX�Btrue=�E�B���h�E���[�h
	ChangeWindowMode(true);
	//��ʃ��[�h�̕ύX
	SetGraphMode(ScreenWidth, ScreenHeight, 32);
	//�`���O���t�B�b�N�̈�𗠂�
	SetDrawScreen(DX_SCREEN_BACK);
	//�L�[���̎擾�Ə�����
	key = new char[ControlKeyNum];
	UpdateKey();

	wallSpawner = new WallSpawner;
	//�ŏ��̃V�[�����쐬
	scene = new Play(wallSpawner);

	//�J�����̎���͈͂�ݒ�
	SetCameraNearFar(nearCameraPos, farCameraPos);
	//�J�����̏ꏊ��ݒ�
	SetCameraPositionAndTarget_UpVecY(CameraPos, VGet(0, 0, 0));

	//���C�g�̌������J��������0,0,0������悤�ɐݒ�

	SetLightDirection(VGet(0, -1, 2));
	//int secondLight = CreateDirLightHandle(VGet(1,-1,2));
	//int thirdLight = CreateDirLightHandle(VGet(-1, -1, 2));

	new Player(leftPlayerPos, Game::MoveDirection::Left, KEY_INPUT_SPACE);
	new Player(rightPlayerPos, Game::MoveDirection::Right, KEY_INPUT_RETURN);

	new Ground(VGet(0, -2.0f, 0));

	DWORD nowTick, prevTick;
	prevTick = timeGetTime();
	deltaTime = 1.0f;
	gameSpeed = 1.0f;

	//��ʍX�V���ɃG���[���N���������AEscape�L�[�������ꂽ��I��
	while (ScreenUpdate() && key[KEY_INPUT_ESCAPE] == 0)
	{
		DeltaTimeSet(nowTick, prevTick);
		UpdateKey();

		ActorUpdate();
		scene->Update();

		DrawModel();
		scene->Render();

		SceneChange();
	}

	delete[] key;
	delete wallSpawner;
	wallSpawner = nullptr;
	delete scene;
	scene = nullptr;

	ShutDown();
	DeleteLightHandleAll();
	//Dxlib�̏I��
	DxLib_End();

	return;
}

bool Game::ScreenUpdate()
{
	if (ProcessMessage() != 0) return false;
	//��ʂ̗��y�[�W�̓��e��\�y�[�W�ɔ��f����
	if (ScreenFlip() != 0) return false;
	//��ʂ�������
	if (ClearDrawScreen() != 0) return false;
	return true;
}

void Game::UpdateKey()
{
	//�S�Ă̓��͏�Ԃ�tmpKey�Ɋi�[
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);

	//num�Ԗڂ̃L�[��������Ă�������Z
	for (int num = 0; num < ControlKeyNum; num++)
	{
		if (tmpKey[num] != 0)
		{
			key[num]++;
		}
		else
		{
			//������Ă��Ȃ��L�[��0�ɂ���
			key[num] = 0;
		}
	}
}

void Game::SceneChange()
{
	sceneName nextScene = scene->SceneChange();
	switch (nextScene)
	{
	case(sceneName::title):
		delete scene;
		scene = new Title(wallSpawner);
		break;
	case(sceneName::play):
		delete scene;
		scene = new Play(wallSpawner);
		gameSpeed = 1.0f;
		break;
	case(sceneName::clear):
		scene = new Clear(wallSpawner);
		break;
	}
}

void Game::DeltaTimeSet(DWORD& nowTick, DWORD& prevTick)
{
	nowTick = timeGetTime();
	DWORD mTicks = DWORD(nowTick - prevTick);
	prevTick = timeGetTime();

	deltaTime = mTicks / 1000.0f;
	prevTick = nowTick;

	if (deltaTime >= 0.07f)
	{
		deltaTime = 0.07f;
	}
}


void Game::AddActor(Actor * actor)
{
	pendingActors.emplace_back(actor);
}

void Game::RemoveActor(Actor * actor)
{
	//actor��upDateingActors��pendingActors�̒�����폜����
	auto iter = std::find(pendingActors.begin(), pendingActors.end(), actor);
	if (iter != pendingActors.end())
	{
		std::iter_swap(iter, pendingActors.end() - 1);
		pendingActors.pop_back();
	}
	iter = std::find(upDateActors.begin(), upDateActors.end(), actor);
	if (iter != upDateActors.end())
	{
		std::iter_swap(iter, upDateActors.end() - 1);
		upDateActors.pop_back();
	}
}

void Game::ActorUpdate()
{
	//�S�Ă�Actor�̍X�V����
	for (auto actor : upDateActors)
	{
		actor->Update(deltaTime);
	}
	//����F���ōX�V���ׂ�Actor�̏������S�ďI��������actor�ɑ}������
	for (auto actor : pendingActors)
	{
		upDateActors.emplace_back(actor);
	}
	pendingActors.clear();

	//�S�Ă�Actor�̒�����State��NoActive��Actor��deleteActors�Ɉڂ��폜����
	std::vector<Actor *> deleteActors;
	for (auto actor : upDateActors)
	{
		if (actor->GetState() == Actor::ActiveState::NoActive)
		{
			deleteActors.emplace_back(actor);
		}
	}
	//���ׂẴA�N�^�[��delete����
	for (auto actor : deleteActors)
	{
		delete actor;
	}
}

void Game::ShowActor()
{
	//printf("\n\n<-----------------Actor List---------------->\n");
	//printf("--------> Active Actor(%4d) <----------\n", mActors.size());
	//for (auto i : mActors)
	//{
	//	printf("mem[%p] : id %d ", i, i->GetID());
	//	std::cout << typeid(*i).name() << "\n";
	//}
	//printf("\n--------> Pending Actor(%4d) <----------\n", mPendingActors.size());
	//for (auto i : mPendingActors)
	//{
	//	printf("mem[%p] : id %d ", i, i->GetID());
	//	std::cout << typeid(*i).name() << "\n";
	//}
}

void Game::ShutDown()
{
	//upDateActors�̍폜
	while (!upDateActors.empty())
	{
		delete upDateActors.back();
	}
	upDateActors.clear();

	//pendingActors�̍폜
	while (!pendingActors.empty())
	{
		delete pendingActors.back();
	}
	pendingActors.clear();

	//model�֘A�̉��
	for (auto model : originalModel)
	{
		MV1DeleteModel(model);
	}
	originalModel.clear();
	for (auto model : duplicateModel)
	{
		MV1DeleteModel(model.second);
	}
	duplicateModel.clear();
	for (auto model : modelTexture)
	{
		DeleteGraph(model.second);
	}
	modelTexture.clear();

	DxLib::DxLib_End();
}

int Game::LoadModel(const std::string & fileName, const std::string & textureFileName)
{
	/*fileName�̃��f�������ɓǂݍ���ł��Ȃ���
	�^�̏ꍇdupricateModel���̂��̃��f���A�h���X��Ԃ��A
	�U�̏ꍇ�V���ɓǂݍ���Ń��f���A�h���X���i�[����*/
	int modelId;
	auto iter = duplicateModel.find(fileName);
	if (iter != duplicateModel.end())
	{
		modelId = iter->second;
	}
	else
	{
		int originalModelId = MV1LoadModel(fileName.c_str());
		originalModel.push_back(originalModelId);

		modelId = MV1DuplicateModel(originalModelId);
		duplicateModel.emplace(fileName.c_str(), modelId);

	}
	//�e�N�X�`���ł��������Ƃ����Ō��modelId��textureId�𒣂�t����
	int textureId;
	auto textureIter = modelTexture.find(textureFileName);
	if (textureIter != modelTexture.end())
	{
		textureId = textureIter->second;
	}
	else
	{
		textureId = LoadGraph(textureFileName.c_str());
		modelTexture.emplace(textureFileName.c_str(), textureId);
	}
	MV1SetTextureGraphHandle(modelId, 0, textureId, FALSE);

	return modelId;
}

void Game::AddModel(ModelComponent * model)
{
	//����Model�̍X�V�������擾���A���̏������傫���l���������炻�̑O�ɑ}������
	int drawNumber = model->getProccesNumber();
	auto iter = modelComponents.begin();
	for (; iter != modelComponents.end(); ++iter)
	{
		int iterDrawNumber = (*iter)->getProccesNumber();
		if (drawNumber < iterDrawNumber ||
			drawNumber == iterDrawNumber)
		{
			break;
		}
	}
	modelComponents.insert(iter, model);
}

void Game::RemoveModel(ModelComponent * model)
{
	auto iter = std::find(modelComponents.begin(), modelComponents.end(), model);
	if (iter != modelComponents.end())
	{
		modelComponents.erase(iter);
	}
}

void Game::DrawModel()
{
	for (auto model : modelComponents)
	{
		model->DrawModel();
	}
}

void Game::AddBoxCollider(BoxColliderComponent * box)
{
	boxCollider.emplace_back(box);
}

void Game::RemoveCollider(BoxColliderComponent * box)
{
	auto iter = std::find(boxCollider.begin(), boxCollider.end(), box);
	if (iter != boxCollider.end())
	{
		std::iter_swap(iter, boxCollider.end() - 1);
		boxCollider.pop_back();
	}
}

void Game::AddSphereCollider(SphereColliderComponent * sphere)
{
	sphereCollider.emplace_back(sphere);
}

void Game::RemoveSphereCollider(SphereColliderComponent * sphere)
{
	auto iter = std::find(sphereCollider.begin(), sphereCollider.end(), sphere);
	if (iter != sphereCollider.end())
	{
		std::iter_swap(iter, sphereCollider.end() - 1);
		sphereCollider.pop_back();
	}
}

bool Game::CollisionCall()
{
	for (auto ball : sphereCollider)
	{
		for (auto box : boxCollider)
		{
			//�ǂ̏Փˏ����t���O�������Ă��Ȃ��ꍇ�����ŏI������
			if (!box->GetIsCollision())
			{
				continue;
			}
			bool end = CollisionBallWall(ball, box);
			if (end)
			{
				//�����ǂ������ꍇ�AgameSpeed������������
				if (box->GetTag() == BoxColliderComponent::ColliderTag::AddSpeedWall)
				{
					box->OnCollision();
					ball->OnCollision();
					
					continue;
				}
				//Player��������Ԃ������ꍇ�A�ǂ�Pause�ɂ���
				if (ball->GetTag() == SphereColliderComponent::CollisionTag::SuperPlayer)
				{
					box->OnCollision();
					continue;
				}
				return end;
			}
		}
	}
	return false;
}

bool Game::CollisionBallWall(SphereColliderComponent * ball, BoxColliderComponent * wall)
{
	SphereInfo sphere = ball->GetInfo();
	BoxInfo box = wall->GetIndo();

	float sphereLengh = sphere.length*sphere.length;
	sphereLengh = 1;
	box.length = 1;


	if (box.position.x == sphere.position.x)
	{
		return true;
	}

	VECTOR boxLeftUp = VGet(box.position.x - box.length, box.position.y + box.length, 0);

	if (((boxLeftUp.x - sphere.position.x)*(boxLeftUp.x - sphere.position.x)) +
		((boxLeftUp.y - sphere.position.y)*(boxLeftUp.y - sphere.position.y)) <= sphereLengh)
	{
		return true;
	}

	VECTOR boxRightDown = VGet(box.position.x + box.length, box.position.y - box.length, 0);
	{
		if (((boxRightDown.x - sphere.position.x)*(boxRightDown.x - sphere.position.x)) +
			((boxRightDown.y - sphere.position.y)*(boxRightDown.y - sphere.position.y)) <= sphereLengh)
		{
			return true;
		}
	}
	return false;
}
