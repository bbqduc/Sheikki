#include "tank.h"
#include "engine.h"


	Tank::Tank(const Model& model):
	Entity(model) {}

void Tank::fire(Engine& engine)
{
	Projectile* proj = new Projectile(engine.getModel("bullet"), 100.0f);
	proj->setPos(position[3][0], position[3][1], position[3][2]);
	proj->rotate(orientation);
	proj->setVelocity(0.1f);
	glm::vec3 dir=glm::vec3(orientation[1]);
	proj->setDirection(dir);

	engine.addProjectile(proj);
}

void Tank::tick(bool keysDown[], Engine& engine)
{
	Entity::tick(keysDown);
	if(keysDown[Engine::SPACE])
	{
		fire(engine);
		keysDown[Engine::SPACE] = false;
	}
}

void Tank::tick()
{
	Entity::tick();
}
