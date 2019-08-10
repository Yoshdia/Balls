#pragma once

#include "DxLib.h"
#include "component.h"
#include <string>
class Actor;

class ModelComponent : public Component
{
public:
	ModelComponent(Actor* owner, int setProcessNumber);
	//モデルに変更を加えないActorに呼ばせる、Loadやscaleを最初にまとめて設定するインスタンス
    ModelComponent(Actor* owner, int setProcessNumber, VECTOR scale, const std::string& fileName);
	virtual ~ModelComponent();
	virtual void DrawModel();
	virtual void SetModel(int model);
	void SetModelScale(VECTOR scale) ;
	void SetModel(int model, int tex);

	static const int DrawPlayerNumber;
	static const int DrawWallNumber;
	static const int DrawBoxEffectNumber;
	static const int DrawGrainNumber;
protected:
	//このComponentが所持しているモデルのポインタ(読み込みエラーの際は-1が入るため初期値にも-1を入れる)
	int modelId;
};