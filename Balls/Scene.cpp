#include "Scene.h"

Scene::Scene(DeepestSpawner * pDeepestSpawn, Player * pLeftPlayer, Player * pRightPlayer, Score * pScore)
{
	 deepestSpawner = pDeepestSpawn;
	 leftPlayer=pLeftPlayer;
	 rightPlayer=pRightPlayer;
	 score = pScore; 
}
