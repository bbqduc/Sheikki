#include "engine.h"
#include "vec.h"
#include "model.h"
#include "entity.h"
#include "3ds_loader.h"
/*
Model createSimpleTriangleModel()
{

	Vec<float, 3>* vertices = new Vec<float, 3>[3];
	Vec<float, 3>* colors = new Vec<float, 3>[3];
	Vec<float, 2>* texcoords = new Vec<float, 2>[3];
	Vec<GLuint, 3>* polygons = new Vec<GLuint, 3>;

	colors[0][0] = 0.5f;
	colors[0][1] = 0.5f;
	colors[0][2] = 0.5f;
	for(int i = 1; i < 3; ++i){
		colors[i][0] = 1;
		colors[i][1] = 1;
		colors[i][2] = 1;
	}

	texcoords[0][0] = 0;
	texcoords[0][1] = 0;

	texcoords[1][0] = 0.0f;
	texcoords[1][1] = 1;

	texcoords[2][0] = 1;
	texcoords[2][1] = 0.0f;

	vertices[0][0] = -0.5f;
	vertices[0][1] = 0;
	vertices[0][2] = -0.5f;

	vertices[1][0] = 0.5f;
	vertices[1][1] = 0;
	vertices[1][2] = -0.5f;

	vertices[2][0] = 0;
	vertices[2][1] = 0;
	vertices[2][2] = 0.5f;

	polygons[0][0] = 0;
	polygons[0][1] = 1;
	polygons[0][2] = 2;

//	Model model(3, 1, vertices, polygons, texcoords, GL_TRIANGLES, "TEXTURE_TEST.png");
	Model model(3, 1, vertices, polygons, colors, GL_TRIANGLES);
	delete[] vertices;
	delete[] colors;

	return model;
}*/

int main()
{
	Engine engine;

//	Model model = createSimpleTriangleModel();
	Model model = Model_Loader_3ds::read_model("box.3ds");
	Model plane = Model_Loader_3ds::read_model("plane.3ds");
	Entity entity = Entity(&model);
	Entity plane_e = Entity(&plane);

	engine.addEntity(&entity);

	SimpleShader s("minimal.vert","dark.frag");
	engine.addEntity(&plane_e, &s);

	plane_e.rotatePitch(3.14f/2);
	plane_e.move(0,-3,5);
	entity.rotatePitch(3.14f / 2);
	entity.move(0,0,5);
	engine.setActive(&entity); // Sets entityInTheEngine to be the target of user input (for example movement)
	engine.gameLoop();

	return EXIT_SUCCESS;
}
