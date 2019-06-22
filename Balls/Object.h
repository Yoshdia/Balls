#pragma once

#include "DxLib.h"

class Object
{
public:
	Object() ;
	virtual ~Object() ;
protected:


	virtual void Update() {};
	virtual void Render() {};
};

