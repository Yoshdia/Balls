#pragma once

#include "BackGround.h"
class BackGround;
class ModelComponent;

class GrainBackGround :
	public BackGround
{
public:
	GrainBackGround(const std::string & fileName,const VECTOR& modelScale);
	~GrainBackGround();

	void ResetBackGround(VECTOR pos, VECTOR targetPos);
private:
	void UpdateBack(float deltaTime);
	ModelComponent* modelComponent;
	static const VECTOR MoveSpeed;
};

