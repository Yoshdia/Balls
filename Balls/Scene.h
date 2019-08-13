#pragma once

enum sceneName
{
	noChange,
	title,
	play,
	clear,
};

#include "DeepestSpawner.h"
#include "Score.h"
#include "Player.h"

//Scene���N���X
class Scene
{
public:
	Scene(DeepestSpawner* pDeepestSpawn, Player* pLeftPlayer,Player* pRightPlayer,Score* pScore) ;
	virtual ~Scene() {};
	//�X�V
	virtual void Update(float deltaTime) {};
	//�`��
	virtual void Render() {};
	//���ꂼ���Scene�ŕʃV�[���Ɉړ���������Ɩ��O���w��ł���
	virtual sceneName SceneChange() = 0;
protected:
	DeepestSpawner* deepestSpawner;
		Score* score;
		Player* leftPlayer;
		Player* rightPlayer;
};