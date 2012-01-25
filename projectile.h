#include "entity.h"

class Projectile : public Entity
{
	GLfloat TTL;
public:
	Projectile(const Model&, GLfloat);
	void tick();
	GLfloat getTTL() { return TTL; }
};