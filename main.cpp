#include "engine.h"
#include "model.h"
#include "entity.h"
#include "3ds_loader.h"

int main()
{

	Engine engine;

	Model model = Model_Loader_3ds::read_model("test.3ds");
	Model plane = Model_Loader_3ds::read_model("plane.3ds");
	Entity entity = Entity(&model);
	Entity plane_e = Entity(&plane);

	engine.addEntity(&entity);

	SimpleShader dark("minimal.vert","dark.frag");
	SimpleShader plain("minimal.vert","plain.frag");
	engine.addShader(&plain);
	engine.addEntity(&plane_e, &dark);

	plane_e.rotatePitch(90.0f);
	plane_e.move(0,-3,0);

	entity.rotatePitch(90.0f);
	entity.move(0,0,5);
	engine.setActive(&entity); // Sets entityInTheEngine to be the target of user input (for example movement)
	engine.gameLoop();

	return EXIT_SUCCESS;
}
