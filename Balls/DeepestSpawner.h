#pragma once

class GrainBackGroundHaver;

class DeepestSpawner
{
public:
	DeepestSpawner();
	~DeepestSpawner();

	void SpawnerUpdate(float deltaTime);
private:
	void GrainSpawn(float deltaTime);
	GrainBackGroundHaver* grains;
	VECTOR myPos;
	float count;
	bool rightMoving;
	static const float Radius;
};

