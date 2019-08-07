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

//Scene基底クラス
class Scene
{
public:
	Scene(DeepestSpawner* pDeepestSpawn, Score* pScore) { deepestSpawner = pDeepestSpawn; score = pScore; };
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
};