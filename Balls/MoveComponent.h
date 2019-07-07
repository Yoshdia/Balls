#pragma once

#include "Component.h"
class Actor;

//ó‚¯æ‚Á‚½distance‚ğActor‚ÌÀ•W‚É‰ÁZ‚µ‘±‚¯‚éComponent
class MoveComponent :
	public Component
{
public:
	MoveComponent(Actor* owner ,int processNumber, VECTOR distance);
	~MoveComponent();
	void Update(float deltaTime);
protected:
	//À•W‚ÉmoveDistance‚ğ‘«‚·‚¾‚¯‚ÌŠÖ”
	void Move(float deltaTime);
	//Œp³æ‚©‚çŒÄ‚Î‚ê‚éAdeltaTime‚ğŒp³æ‚ÅŒvZ‚·‚é‚½‚ßˆø”‚âŠÖ”“à‚ÉdeltaTime‚ª‚È‚¢MoveŠÖ”
	void Move();
	VECTOR position;
	//–ˆFˆÚ“®‚·‚é‹——£
	VECTOR moveDistance;
};

