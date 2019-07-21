#include "Actor.h"
#include "EffectFactory.h"
#include "BlockEffect.h"

EffectFactory* EffectFactory::effectFactory = nullptr;
const int EffectFactory::BlockNum = 10;

void EffectFactory::Create()
{
	if (!effectFactory)
	{
		effectFactory = new EffectFactory();
		effectFactory->CreatePauseEffect();
	}
}

void EffectFactory::Delete()
{
	delete effectFactory;
	effectFactory = nullptr;
}

void EffectFactory::PopEffect(const VECTOR& effectPos,const EffectFactory::Effects& name)
{
	switch (name)
	{
	case(EffectFactory::Effects::Block):
		PopTripleBlock(effectPos);
		break;
	}
}

void EffectFactory::CreatePauseEffect()
{
	for (int num = 0; num < BlockNum; num++)
	{
		blockEffect[num] = new BlockEffect();
	}
}

BlockEffect * EffectFactory::GetPauseBlock()
{
	for (int num = 0; num < BlockNum; num++)
	{
		if (blockEffect[num]->GetState() == Actor::ActiveState::Paused)
		{
			return blockEffect[num];
		}
	}
	return nullptr;
}

void EffectFactory::PopTripleBlock(const VECTOR& pos)
{
	BlockEffect* block = GetPauseBlock();
	block->ResetBlock(pos, BlockEffect::BlockMoveDirection::LeftUp);
	block = GetPauseBlock();
	block->ResetBlock(pos, BlockEffect::BlockMoveDirection::LeftDown);
	block = GetPauseBlock();
	block->ResetBlock(pos, BlockEffect::BlockMoveDirection::RightUp);
	block = GetPauseBlock();
	block->ResetBlock(pos, BlockEffect::BlockMoveDirection::RightDown);
}

