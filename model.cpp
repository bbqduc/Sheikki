#include "model.h"
#include "sheikki_wrappers.h"
#include <iostream>

// Private constructor used by Model_3ds_loader
Model::Model():
	num_vertices(0),
	num_polygons(0),
	vertices(NULL),
	texcoords(NULL),
	polygons(NULL)
{}

Model::Model(int num_vertices_, int num_polygons_, Vec<float, 3>* vertices_, Vec<GLuint, 3>* polygons_, GLint drawMode_) :
	num_vertices(num_vertices_),
	num_polygons(num_polygons_),
	vertices(new Vec<float, 3>[num_vertices_]),
	texcoords(NULL),
	polygons(new Vec<GLuint, 3>[num_polygons]),
	drawMode(drawMode_),
	texture(0)
{
	for(int i = 0; i < num_vertices; ++i)
		vertices[i] = vertices_[i];
	for(int i = 0; i < num_polygons; ++i)
		polygons[i] = polygons_[i];
	InitVBOs();
}

Model::Model(int num_vertices_, int num_polygons_, Vec<float, 3>* vertices_, Vec<GLuint, 3>* polygons_, Vec<float, 2>* texcoords_, GLint drawMode_, std::string texturepath) :
	num_vertices(num_vertices_),
	num_polygons(num_polygons_),
	vertices(new Vec<float, 3>[num_vertices_]),
	texcoords(new Vec<float, 2>[num_vertices_]),
	polygons(new Vec<GLuint, 3>[num_polygons_]),
	drawMode(drawMode_),
	texture(0)
{
	for(int i = 0; i < num_vertices; ++i)
	{
		vertices[i] = vertices_[i];
		texcoords[i] = texcoords_[i];
	}

	for(int i = 0; i < num_polygons; ++i)
		polygons[i] = polygons_[i];

	InitVBOs();

	Init_Texture(texturepath);

}

void Model::calculate_normals()
{
	normals = new Vec<float, 3>[num_vertices];	
	for(int i = 0; i < num_vertices; ++i)
		normals[i] *= 0;

	Vec<float, 3> a_to_b, a_to_c;

	for(int i = 0; i < num_polygons; ++i)
	{
		a_to_b = vertices[polygons[i][1]] - vertices[polygons[i][0]];
		a_to_c = vertices[polygons[i][2]] - vertices[polygons[i][0]];

		Vec<float, 3> cross_product = cross(a_to_b, a_to_c);
		cross_product.set_length(1.0f);

		for(int j = 0; j < 3; ++j)
			normals[polygons[i][j]] += cross_product;
	}

	for(int i = 0; i < num_vertices; ++i)
		normals[i].set_length(1.0f);
}

void Model::Init_Texture(const std::string& texturepath)
{
	// Load image, initialize texture and destroy the image.
	sf::Image tmp;
	tmp.LoadFromFile(texturepath);

	const sf::Uint8* texturedata = tmp.GetPixelsPtr();
  	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// OpenGL texture parameter magic.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);

	// Generate the texture. RGBA channels are required.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tmp.GetWidth(), tmp.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texturedata);
}


void Model::InitVBOs()
{
	calculate_normals();
	// initialize VAO
	sheikki_glGenVertexArrays(1, &VAO_id);
	sheikki_glBindVertexArray(VAO_id);

	// initialize VBO for model vertices and polygon vertex indices
	glGenBuffers(1, &VBO_vertices_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices_id);
	glBufferData(GL_ARRAY_BUFFER, num_vertices*sizeof(Vec<float, 3>), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec<float, 3>), 0);

	// initialize VBO for normals of vertices
	glGenBuffers(1, &VBO_normals_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_normals_id);
	glBufferData(GL_ARRAY_BUFFER, num_vertices*sizeof(Vec<float, 3>), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vec<float, 3>), 0);

	if (texcoords != NULL)
	{
		glGenBuffers(1, &VBO_texcoord_id);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_texcoord_id);
		glBufferData(GL_ARRAY_BUFFER, num_vertices*sizeof(Vec<float, 2>), &texcoords[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vec<float, 2>), 0);
	}

	glGenBuffers(1, &VBO_indices_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_indices_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_polygons*sizeof(Vec<GLuint, 3>), &polygons[0][0], GL_STATIC_DRAW);

	sheikki_glBindVertexArray(0);
}

GLuint Model::GetTexture() const
{
	return texture;
}

Model::~Model()
{
	delete[] vertices;
}
