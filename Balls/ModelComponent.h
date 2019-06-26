#pragma once

#include "Game.h"
#include "component.h"

class ModelComponent : public Component
{
public:
	ModelComponent(class Actor* owner,int drawNumber=100);//int drawOrder = 100
	~ModelComponent();
	virtual void DrawModel();
	virtual void SetModel(int model);
	void SetModelScale(float scale) ;

protected:
	//このComponentが所持しているモデルのポインタ(読み込みエラーの際は-1が入るため初期値にも-1を入れる)
	int modelId;//mModelID;

};