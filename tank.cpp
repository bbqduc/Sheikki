#include "tank.h"
#include "engine.h"

	Tank::Tank(const Model& model):
	Entity(model),
	cannonCoolDown(100.0f)
	{}

void Tank::fire(Engine& engine)
{
	Projectile* proj = new Projectile(engine.getModel("bullet"), 10.0f);
	proj->setPos(position[3][0], position[3][1], position[3][2]);
	proj->rotate(orientation);
	proj->setVelocity(0.1f);
	glm::vec3 dir=glm::vec3(orientation[1]);
	proj->setDirection(dir);

	engine.addProjectile(proj);
	cannonCoolDown = 100.0f;
}

void Tank::tick(bool keysDown[], Engine& engine)
{
	Entity::tick(keysDown);
	if(keysDown[Engine::SPACE] && cannonCoolDown < 0)
	{
		fire(engine);
	}
}

void Tank::tick()
{
	Entity::tick();
	if(cannonCoolDown >= 0.0f)
		cannonCoolDown -= 0.1f;
}
