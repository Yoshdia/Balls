#pragma once

enum sceneName
{
	noChange,
	title,
	play,
	clear,
};

//Scene基底クラス
class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};
	//更新
	virtual void Update() {};
	//描画
	virtual void Render() {};
	//それぞれのSceneで別シーンに移動する条件と名前を指定できる
	virtual sceneName SceneChange(char* key) = 0;
};