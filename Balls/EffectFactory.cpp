#include "Actor.h"
#include "EffectFactory.h"
#include "BlockEffect.h"
#include "LineEffect.h"

EffectFactory* EffectFactory::effectFactory = nullptr;
const int EffectFactory::BlockNum = 10;
const int EffectFactory::LineNum = 10;

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
	case(EffectFactory::Effects::Line):
		PopAddSpeedLine(effectPos);
		break;
	}
}

void EffectFactory::CreatePauseEffect()
{
	for (int num = 0; num < BlockNum; num++)
	{
		blockEffect[num] = new BlockEffect();
	}
	for (int num = 0; num < LineNum; num++)
	{
		lineEffect[num] = new LineEffect();
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
	return new BlockEffect();
}

LineEffect * EffectFactory::GetPauseLine()
{
	for (int num = 0; num < LineNum; num++)
	{
		if (lineEffect[num]->GetState() == Actor::ActiveState::Paused)
		{
			return lineEffect[num];
		}
	}
	return new LineEffect();
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

void EffectFactory::PopAddSpeedLine(const VECTOR & pos)
{
	VECTOR linePos=VGet(0,0,0);
	LineEffect* line;

	line = GetPauseLine();
	linePos = VGet(2, 4, pos.z);
	line->ResetLine(linePos);
	line = GetPauseLine();
	linePos = VGet(-2, 4, pos.z);
	line->ResetLine(linePos);
	line = GetPauseLine();
	linePos = VGet(4, 2, pos.z);
	line->ResetLine(linePos);
	line = GetPauseLine();
	linePos = VGet(-4, 2, pos.z);
	line->ResetLine(linePos);
}

