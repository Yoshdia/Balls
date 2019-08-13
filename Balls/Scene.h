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

//Scene基底クラス
class Scene
{
public:
	Scene(DeepestSpawner* pDeepestSpawn, Player* pLeftPlayer,Player* pRightPlayer,Score* pScore) ;
	virtual ~Scene() {};
	//更新
	virtual void Update(float deltaTime) {};
	//描画
	virtual void Render() {};
	//それぞれのSceneで別シーンに移動する条件と名前を指定できる
	virtual sceneName SceneChange() = 0;
protected:
	DeepestSpawner* deepestSpawner;
		Score* score;
		Player* leftPlayer;
		Player* rightPlayer;
};