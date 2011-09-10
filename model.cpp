#include "model.h"
#include "sheikki_wrappers.h"
#include <iostream>

// Private constructor used by Model_3ds_loader
Model::Model():
	num_vertices(0),
	num_polygons(0),
	vertices(NULL),
	colors(NULL),
	texcoords(NULL),
	polygons(NULL)
{}

Model::Model(int num_vertices_, int num_polygons_, Vec<float, 3>* vertices_, Vec<GLuint, 3>* polygons_, Vec<float, 3>* colors_, GLint drawMode_) :
	num_vertices(num_vertices_),
	num_polygons(num_polygons_),
	vertices(new Vec<float, 3>[num_vertices_]),
	colors(new Vec<float, 3>[num_vertices_]),
	texcoords(NULL),
	polygons(new Vec<GLuint, 3>[num_polygons]),
	drawMode(drawMode_),
	texture(0)
{
	for(int i = 0; i < num_vertices; ++i)
	{
		vertices[i] = vertices_[i];
		if(colors != NULL)
			colors[i] = colors_[i];
	}
	for(int i = 0; i < num_polygons; ++i)
		polygons[i] = polygons_[i];
	InitVBOs();
}

Model::Model(int num_vertices_, int num_polygons_, Vec<float, 3>* vertices_, Vec<GLuint, 3>* polygons_, Vec<float, 2>* texcoords_, GLint drawMode_, std::string texturepath) :
	num_vertices(num_vertices_),
	num_polygons(num_polygons_),
	vertices(new Vec<float, 3>[num_vertices_]),
	colors(NULL),
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
	// initialize VAO
	sheikki_glGenVertexArrays(1, &VAO_id);
	sheikki_glBindVertexArray(VAO_id);

	// initialize VBO for model vertices and polygon vertex indices
	glGenBuffers(1, &VBO_vertices_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices_id);
	glBufferData(GL_ARRAY_BUFFER, num_vertices*sizeof(Vec<float, 3>), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec<float, 3>), 0);

	// initialize VBO for colors of vertices
	if(colors != NULL)
	{
		glGenBuffers(1, &VBO_color_id);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_color_id);
		glBufferData(GL_ARRAY_BUFFER, num_vertices*sizeof(Vec<float, 3>), colors[0].coords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vec<float, 3>), 0);
	}

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
