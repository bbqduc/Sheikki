#include "engine.h"
#include "model.h"
#include "entity.h"
#include "3ds_loader.h"

int main()
{

	Engine engine;
	engine.addModel("tank", Model_Loader_3ds::read_model("tank.3ds"));
	engine.addModel("plane", Model_Loader_3ds::read_model("plane.3ds"));
	engine.addModel("bullet", Model_Loader_3ds::read_model("bullet.3ds"));
	
	Entity entity = Entity(engine.getModel("tank"));
	Entity plane_e = Entity(engine.getModel("plane"));

	engine.addEntity(&entity);

	SimpleShader dark("minimal.vert","dark.frag");
	SimpleShader plain("minimal.vert","plain.frag");
	engine.addShader(&plain);
	engine.addEntity(&plane_e, &dark);

	plane_e.rotatePitch(90.0f);
	plane_e.move(0,-3,0);

	entity.move(0,0,5);
	engine.setActive(&entity); // Sets entityInTheEngine to be the target of user input (for example movement)
	engine.gameLoop();

	return EXIT_SUCCESS;
}
