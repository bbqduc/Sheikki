#include "engine.h"
#include "vec.h"
#include "model.h"
#include "entity.h"
#include "3ds_loader.h"

Model createSimpleTriangleModel()
{

	Vec<float, 3>* vertices = new Vec<float, 3>[3];
	Vec<float, 3>* colors = new Vec<float, 3>[3];
	Vec<float, 2>* texcoords = new Vec<float, 2>[3];
	Vec<uint16_t, 3>* polygons = new Vec<uint16_t, 3>;

	colors[0].coords[0] = 0.5f;
	colors[0].coords[1] = 0.5f;
	colors[0].coords[2] = 0.5f;
	for(int i = 1; i < 3; ++i){
		colors[i].coords[0] = 1;
		colors[i].coords[1] = 1;
		colors[i].coords[2] = 1;
	}

	texcoords[0].coords[0] = 0;
	texcoords[0].coords[1] = 0;

	texcoords[1].coords[0] = 0.0f;
	texcoords[1].coords[1] = 1;

	texcoords[2].coords[0] = 1;
	texcoords[2].coords[1] = 0.0f;

	vertices[0].coords[0] = -0.5f;
	vertices[0].coords[1] = 0;
	vertices[0].coords[2] = -0.5f;

	vertices[1].coords[0] = 0.5f;
	vertices[1].coords[1] = 0;
	vertices[1].coords[2] = -0.5f;

	vertices[2].coords[0] = 0;
	vertices[2].coords[1] = 0;
	vertices[2].coords[2] = 0.5f;

	polygons[0][0] = 0;
	polygons[0][1] = 1;
	polygons[0][2] = 2;

	Model model(3, 1, vertices, polygons, texcoords, GL_TRIANGLES, "TEXTURE_TEST.png");
//	Model model(3, 1, vertices, polygons, colors, GL_TRIANGLES);
	delete[] vertices;
	delete[] colors;

	return model;
}

int main()
{
	Engine engine;

	Model model = createSimpleTriangleModel();
//	Model model = Model_Loader_3ds::read_model("box.3ds");
	Entity* entity = new Entity(&model);

	(engine.addEntity(*entity)).setPos(0.5,0.5,3);
	Entity& entityInTheEngine = engine.addEntity(*entity); // Need the reference because entity is copied by value to engines list of objects
								// Maybe not the best way but at least cleaner memory management
	delete entity;

	entityInTheEngine.rotatePitch(3.14f / 2);
	entityInTheEngine.move(0,0,5);
	engine.setActive(entityInTheEngine); // Sets entityInTheEngine to be the target of user input (for example movement)
	engine.gameLoop();

	return EXIT_SUCCESS;
}
