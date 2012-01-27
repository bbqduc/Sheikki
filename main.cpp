#include "engine.h"
#include "model.h"
#include "entity.h"
#include "3ds_loader.h"
#include "tank.h"

int main()
{


	Engine engine;
	{
		Model tank = Model_Loader_3ds::read_model("tank.3ds", "camouflage.jpg"),
			plane = Model_Loader_3ds::read_model("plane.3ds", "ground.jpg"),
			bullet = Model_Loader_3ds::read_model("bullet.3ds", "TEXTURE_TEST.png"),
			sphere = Model_Loader_3ds::read_model("sphere.3ds", "");
		engine.addModel("tank", tank);
		engine.addModel("plane", plane);
		engine.addModel("bullet", bullet);
		engine.addModel("sphere", sphere);
	}

	Tank entity = Tank(engine.getModel("tank"));
	Entity plane_e = Entity(engine.getModel("plane"));

	PhongShader phong("phong.vert","phong.frag");
	engine.addShader(&phong);

	engine.addTank(&entity, &phong);
	engine.addObject(&plane_e, &phong);

	plane_e.rotatePitch(90.0f);
	plane_e.move(0,-3,0);

	entity.move(0,0,5);
	engine.setActive(&entity); // Sets entityInTheEngine to be the target of user input (for example movement)
	engine.gameLoop();

	return EXIT_SUCCESS;
}
