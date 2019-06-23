#pragma once

#include "Game.h"
#include "component.h"

class ModelComponent : public Component
{
public:
	ModelComponent(class Actor* owner, int drawOrder = 100);
	~ModelComponent();
	virtual void Draw();
	virtual void SetModel(int modelID);

	int GetDrawOrder() const { return mDrawOrder; }

protected:
	int mModelID;
	int mDrawOrder;
};