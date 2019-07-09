#pragma once

enum sceneName
{
	noChange,
	title,
	play,
	clear,
};

#include "WallSpawner.h"

//Scene基底クラス
class Scene
{
public:
	Scene(WallSpawner* pSpawn) { wallSpawner = pSpawn; };
	virtual ~Scene() {};
	//更新
	virtual void Update(float deltaTime) {};
	//描画
	virtual void Render() {};
	//それぞれのSceneで別シーンに移動する条件と名前を指定できる
	virtual sceneName SceneChange() = 0;
protected:
	WallSpawner* wallSpawner;
};