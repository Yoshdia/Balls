#include "DxLib.h"
#include "Scene.h"
#include "Player.h"
#include "Title.h"
#include "Play.h"
#include "Clear.h"
#include "Wall.h"
#include "WallSetter.h"
#include "Actor.h"
#include"ModelComponent.h"


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

char * Game::GetAllInputKey()
{
	return key;
}

void Game::Update()
{
	//dxlib��������
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
	SetUpdateKey();

	//�ŏ��̃V�[�����쐬
	scene = new Play;

	//�J�����̎���͈͂�ݒ�
	SetCameraNearFar(nearCameraPos, farCameraPos);
	//�J�����̏ꏊ��ݒ�
	SetCameraPositionAndTarget_UpVecY(CameraPos, VGet(0, 0, 0));
	//���C�g�̏ꏊ���J�����Ɠ����ʒu�ɐݒ�
	SetLightPosition(CameraPos);
	//���C�g�̌������J��������0,0,0������悤�ɐݒ�
	SetLightDirection(VGet(0, 0, 1));

	int *playerModel;
	playerModel = new int;
	*playerModel=MV1LoadModel("model/whiteBall.mqo");
	int *playerModelTexture;
	playerModelTexture = new int;
	*playerModelTexture = NULL;
	*playerModelTexture = LoadGraph("model/grade.JPG");

	Player *leftPlayer = new Player(leftPlayerPos, Game::MoveDirection::Left,KEY_INPUT_SPACE,*playerModel, *playerModelTexture);
	Player *rightPlayer = new Player(rightPlayerPos, Game::MoveDirection::Right,KEY_INPUT_RETURN,*playerModel, *playerModelTexture);

	//WallSetter *wallSetter = new WallSetter;
	//wallSetter->SetWall();
	Wall *wall = new Wall;

	mDeltaTime = 0;

	//��ʍX�V���ɃG���[���N���������AEscape�L�[�������ꂽ��I��
	while (ScreenUpdate() && key[KEY_INPUT_ESCAPE] == 0)
	{
		SetUpdateKey();

		ActorUpdate();
		scene->Update();

		wall->Update();
		//wallSetter->Update();

		scene->Render();
		leftPlayer->Render();
		rightPlayer->Render();
		wall->Render();
		Game::GetInstance()->DrawModel();
		//wallSetter->Render();
		DrawGraph(10,10,*playerModelTexture,TRUE);

		SceneChange();


	}
	 
	delete[] key;
	delete scene;
	//delete leftPlayer;
	//delete rightPlayer;
	delete wall;
	//delete wallSetter;

	MV1DeleteModel(*playerModel);
	delete playerModel;
	playerModel = NULL;
	DeleteGraph(*playerModelTexture);
	delete playerModelTexture;
	playerModelTexture = NULL;
	ShutDown();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

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

void Game::SetUpdateKey()
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
		scene = new Title;
		break;
	case(sceneName::play):
		delete scene;
		scene = new Play;
		break;
	case(sceneName::clear):
		scene = new Clear;
		break;
	}
}

void Game::AddActor(Actor * actor)
{
	mPendingActors.emplace_back(actor);
}

void Game::RemoveActor(Actor * actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}
	// ����̓A�N�e�B�u�A�N�^�[���ɂ���H
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::ActorUpdate()
{
	// ���ׂẴA�N�^�[�̍X�V����
	for (auto actor : mActors)
	{
		actor->Update(mDeltaTime);
	}
	// �y���f�B���O���A�N�^�[
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	//�@���ׂẴA�N�^�[�����玀��ł���A�N�^�[��deadActors��
	std::vector<Actor *>deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}
	//���ׂẴA�N�^�[��delete����
	for (auto actor : deadActors)
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
	//�X�v���C�g�R���|�[�l���g�̍폜


	//�A�N�^�[�̍폜
	while (!mActors.empty())
	{
		delete mActors.back();
	}
	mActors.clear();

	//�y���f�B���O�A�N�^�[�̍폜
	while (!mPendingActors.empty())
	{
		delete mPendingActors.back();
	}
	mPendingActors.clear();

	DxLib::DxLib_End();
}

int Game::GetTexture(const std::string & fileName)
{
	int retID;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		retID = iter->second;
	}
	else
	{
		/*retID = LoadGraph(fileName.c_str());*/
		retID=MV1LoadModel(fileName.c_str());

		//���f�����k��
		float scale = 0.1f;
		MV1SetScale(retID, VGet(scale, scale, scale));

		mTextures.emplace(fileName.c_str(), retID);
	}
	return retID;
}

void Game::AddModel(ModelComponent * model)
{
	//�\�[�g���ꂽ�x�N�g�����̑}���_��������
	//���̃��f�����]�񂾕`�揇�Ԃ̒ʂ�ɑ}�����Ă��
	int myDrawOrder = model->GetDrawOrder();
	auto iter = mModels.begin();
	for (;
		iter != mModels.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	mModels.insert(iter, model);
}

void Game::RemoveModel(ModelComponent * model)
{
	auto iter = std::find(mModels.begin(), mModels.end(), model);
	if (iter != mModels.end())
	{
		mModels.erase(iter);
	}
}

void Game::DrawModel()
{
	for (auto model : mModels)
	{
		model->Draw();
	}
}

