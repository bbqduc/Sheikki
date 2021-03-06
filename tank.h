#pragma once
#include "entity.h"

class Engine;

class Tank: public Entity
{
	float cannonCoolDown;
	void fire(Engine&);
public:
	Tank(const Model&);
	void tick();
	void tick(bool[], Engine&);
};
