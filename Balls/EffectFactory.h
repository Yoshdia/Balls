#pragma once

class BlockEffect;
class LineEffect;

class EffectFactory

{
public:
	enum Effects
	{
		Block,
		Line,
	};

	static EffectFactory* GetInstance() { return effectFactory; }
	static void Create();
	static void Delete();

	void PopEffect(const VECTOR& effectPos, const EffectFactory::Effects& name) ;

	~EffectFactory() {};
private:
	static EffectFactory* effectFactory;
	EffectFactory() {};

	void CreatePauseEffect();
	BlockEffect* blockEffect[10];
	BlockEffect* GetPauseBlock();
	LineEffect* lineEffect[10];
	LineEffect* GetPauseLine();
	static const int BlockNum;
	static const int LineNum;

	void PopTripleBlock(const VECTOR& pos);
	void PopAddSpeedLine(const VECTOR& pos);
};

