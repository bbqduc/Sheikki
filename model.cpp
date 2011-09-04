#include "model.h"
#include <iostream>

Model::Model(int numVertices_, Vec3* vertices_, Vec3* colors_, GLint drawMode_) :
	numVertices(numVertices_),
	vertices(new Vec3[numVertices_]),
	colors(new Vec3[numVertices_]),
	texcoords(NULL),
	drawMode(drawMode_),
	texture(0)
{
	for(int i = 0; i < numVertices; ++i)
	{
		vertices[i] = vertices_[i];
		if(colors != NULL)
			colors[i] = colors_[i];
	}
	InitVBOs();
}

Model::Model(int numVertices_, Vec3* vertices_, Vec3* texcoords_, GLint drawMode_, std::string texturepath) :
	numVertices(numVertices_),
	vertices(new Vec3[numVertices_]),
	colors(NULL),
	texcoords(new Vec3[numVertices_]),
	drawMode(drawMode_),
	texture(0)
{
	for(int i = 0; i < numVertices; ++i)
	{
		vertices[i] = vertices_[i];
		texcoords[i] = texcoords_[i];
	}

	InitVBOs();

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
	// initialize VBO for model vertices
	glGenBuffers(1, &VBOid);
	glBindBuffer(GL_ARRAY_BUFFER, VBOid);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vec3), &vertices[0], GL_STATIC_DRAW);

	// initialize VBO for colors of vertices
	if(colors != NULL)
	{
		glGenBuffers(1, &colorid);
		glBindBuffer(GL_ARRAY_BUFFER, colorid);
		glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vec3), colors[0].coords, GL_STATIC_DRAW);
	}

	if (texcoords != NULL)
	{
		glGenBuffers(1, &texcoordid);
		glBindBuffer(GL_ARRAY_BUFFER, texcoordid);
		glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vec3), &texcoords[0], GL_STATIC_DRAW);
	}
}

GLuint Model::GetTexture() const
{
	return texture;
}

Model::~Model()
{
	delete[] vertices;
}
