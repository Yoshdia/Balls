#include "Object.h"



Object::Object()
{
	model = new int;
	*model = NULL;
	duplicateModel = new int;
	*duplicateModel = NULL;
	modelTexture = new int;
	*modelTexture = NULL;
}

Object::~Object()
{
	MV1DeleteModel(*model);
	delete model;
	model = NULL;
	MV1DeleteModel(*duplicateModel);
	delete duplicateModel;
	duplicateModel = NULL;

	delete modelTexture;
	modelTexture = NULL;
}
