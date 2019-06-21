#pragma once

#include "Object.h"

class Wall :
	protected Object
{
public:
	Wall();
	~Wall();

	void Update();
	void Render();
private:
	float movingSpeed;
};

