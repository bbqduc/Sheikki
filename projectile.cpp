#include "projectile.h"
#include <iostream>


	Projectile::Projectile(const Model& model, GLfloat TTL_):
	Entity(model),
		TTL(TTL_)
	{}

	void Projectile::tick()
	{
		Entity::tick();
		TTL -= 0.1f;
		if(TTL < 0)
			std::cout << "KABOOOOOOOOOOOOOOMMMMMMMMMMMMM!\n";
	}