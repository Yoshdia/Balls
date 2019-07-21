#pragma once

class BlockEffect;

class EffectFactory

{
public:
	enum Effects
	{
		Block,
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
	static const int BlockNum;

	void PopTripleBlock(const VECTOR& pos);
};

