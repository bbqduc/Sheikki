#include "engine.h"
#include "vec.h"
#include "model.h"
#include "entity.h"

Model createSimpleTriangleModel()
{

	Vec<3>* vertices = new Vec<3>[3];
	Vec<3>* colors = new Vec<3>[3];
	Vec<3>* texcoords = new Vec<3>[3];

	colors[0].coords[0] = 0.5f;
	colors[0].coords[1] = 0.5f;
	colors[0].coords[2] = 0.5f;
	for(int i = 1; i < 3; ++i){
		colors[i].coords[0] = 0;
		colors[i].coords[1] = 0;
		colors[i].coords[2] = 0;
	}

	texcoords[0].coords[0] = 0;
	texcoords[0].coords[1] = 0;
	texcoords[0].coords[2] = 0;

	texcoords[1].coords[0] = 0.0f;
	texcoords[1].coords[1] = 1;
	texcoords[1].coords[2] = 0;

	texcoords[2].coords[0] = 1;
	texcoords[2].coords[1] = 0.0f;
	texcoords[2].coords[2] = 0;

	vertices[0].coords[0] = -0.5f;
	vertices[0].coords[1] = 0;
	vertices[0].coords[2] = -0.5f;

	vertices[1].coords[0] = 0.5f;
	vertices[1].coords[1] = 0;
	vertices[1].coords[2] = -0.5f;

	vertices[2].coords[0] = 0;
	vertices[2].coords[1] = 0;
	vertices[2].coords[2] = 0.5f;

	Model model(3, vertices, texcoords, GL_TRIANGLES, "TEXTURE_TEST.png");
	delete[] vertices;
	delete[] colors;

	return model;
}

int main()
{
	Engine engine;

	Model model = createSimpleTriangleModel();
	Entity* entity = new Entity(&model);

	(engine.addEntity(*entity)).setPos(0.5,0.5,3);
	Entity& entityInTheEngine = engine.addEntity(*entity); // Need the reference because entity is copied by value to engines list of objects
								// Maybe not the best way but at least cleaner memory management
	delete entity;

	engine.setActive(entityInTheEngine); // Sets entityInTheEngine to be the target of user input (for example movement)
	engine.gameLoop();

	return EXIT_SUCCESS;
}
