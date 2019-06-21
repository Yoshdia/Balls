#pragma once

#include "DxLib.h"

class Object
{
public:
	Object() ;
	virtual ~Object() ;
protected:
	VECTOR pos;
	int *model;
	int *duplicateModel;
	int *modelTexture;

	virtual void Update() {};
	virtual void Render() {};
};

