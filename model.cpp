#include "model.h"
#include "sheikki_wrappers.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "DDSLoader.c"

// Private constructor used by Model_3ds_loader
Model::Model():
num_vertices(0),
	num_polygons(0),
	vertices(NULL),
	normals(NULL),
	texcoords(NULL),
	polygons(NULL)
{}

Model::Model(const Model& model):
name(model.name),
	num_vertices(model.num_vertices),
	num_polygons(model.num_polygons),
	vertices(new glm::vec3[num_vertices]),
	normals(new glm::vec3[num_vertices]),
	texcoords(NULL),
	polygons(new glm::uvec3[num_polygons]),
	drawMode(model.drawMode),
	texture(model.texture),
	texturecoords(model.texturecoords),
	VBO_vertices_id(model.VBO_vertices_id),
	VBO_normals_id(model.VBO_normals_id),
	VBO_indices_id(model.VBO_indices_id),
	VBO_color_id(model.VBO_color_id),
	VBO_texcoord_id(model.VBO_texcoord_id),
	VAO_id(model.VAO_id)
{
	if(model.texcoords)
		texcoords = new glm::vec2[num_vertices];
	for(int i = 0; i < num_polygons; ++i)
		polygons[i] = model.polygons[i];
	for(int i = 0; i < num_vertices; ++i)
	{
		vertices[i] = model.vertices[i];
		normals[i] = model.normals[i];
		if(texcoords)
			texcoords[i] = model.texcoords[i];
	}
}

Model::Model(int num_vertices_, int num_polygons_, glm::vec3* vertices_, glm::uvec3* polygons_, GLint drawMode_) :
	num_vertices(num_vertices_),
	num_polygons(num_polygons_),
	vertices(new glm::vec3[num_vertices_]),
	texcoords(NULL),
	polygons(new glm::uvec3[num_polygons]),
	drawMode(drawMode_),
	texture(0)
{
	for(int i = 0; i < num_vertices; ++i)
		vertices[i] = vertices_[i];
	for(int i = 0; i < num_polygons; ++i)
		polygons[i] = polygons_[i];
	InitVBOs();
}

Model::Model(int num_vertices_, int num_polygons_, glm::vec3* vertices_, glm::uvec3* polygons_, glm::vec2* texcoords_, GLint drawMode_, std::string texturepath) :
num_vertices(num_vertices_),
	num_polygons(num_polygons_),
	vertices(new glm::vec3[num_vertices_]),
	texcoords(new glm::vec2[num_vertices_]),
	polygons(new glm::uvec3[num_polygons_]),
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

Model& Model::operator=(const Model& rhs)
{
	if(this!=&rhs)
	{
		name=rhs.name;
		num_vertices=rhs.num_vertices;
		num_polygons=rhs.num_polygons;
		vertices=new glm::vec3[num_vertices];
		polygons=new glm::uvec3[num_polygons];
		texcoords=NULL;
		normals=new glm::vec3[num_vertices];
		drawMode=rhs.drawMode;
		texture=rhs.texture;
		texturecoords=rhs.texturecoords;
		VBO_vertices_id=rhs.VBO_vertices_id;
		VBO_normals_id=rhs.VBO_normals_id;
		VBO_indices_id=rhs.VBO_indices_id;
		VBO_color_id=rhs.VBO_color_id;
		VBO_texcoord_id=rhs.VBO_texcoord_id;
		VAO_id=rhs.VAO_id;
		if(rhs.texcoords)
			texcoords = new glm::vec2[num_vertices];
		for(int i = 0; i < num_polygons; ++i)
			polygons[i] = rhs.polygons[i];
		for(int i = 0; i < num_vertices; ++i)
		{
			vertices[i] = rhs.vertices[i];
			normals[i] = rhs.normals[i];
			if(texcoords)
				texcoords[i] = rhs.texcoords[i];
		}
	}
	return *this;
}

void Model::calculate_normals()
{
	normals = new glm::vec3[num_vertices];	
	for(int i = 0; i < num_vertices; ++i)
		normals[i] *= 0;

	glm::vec3 a_to_b, a_to_c;

	for(int i = 0; i < num_polygons; ++i)
	{
		a_to_b = vertices[polygons[i][1]] - vertices[polygons[i][0]];
		a_to_c = vertices[polygons[i][2]] - vertices[polygons[i][0]];

		glm::vec3 cross_product = glm::cross(a_to_b, a_to_c);
		cross_product = glm::normalize(cross_product);

		for(int j = 0; j < 3; ++j)
			normals[polygons[i][j]] += cross_product;
	}

	for(int i = 0; i < num_vertices; ++i)
		normals[i] = glm::normalize(normals[i]);
}

void Model::Init_Texture(const std::string& texturepath)
{
	/*
	// Load image, initialize texture and destroy the image.
	sf::Image tmp;
	tmp.LoadFromFile(texturepath);

	const sf::Uint8* texturedata = tmp.GetPixelsPtr();

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// OpenGL texture parameter magic.
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);

	// Generate the texture. RGBA channels are required.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tmp.GetWidth(), tmp.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texturedata);
	*/
	texture=loadDDSTexture(texturepath.c_str());

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_2D);
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
	glBufferData(GL_ARRAY_BUFFER, num_vertices*sizeof(glm::vec3), glm::value_ptr(vertices[0]), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	// initialize VBO for normals of vertices
	glGenBuffers(1, &VBO_normals_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_normals_id);
	glBufferData(GL_ARRAY_BUFFER, num_vertices*sizeof(glm::vec3), glm::value_ptr(normals[0]), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	if (texcoords != NULL)
	{
		glGenBuffers(1, &VBO_texcoord_id);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_texcoord_id);
		glBufferData(GL_ARRAY_BUFFER, num_vertices*sizeof(glm::vec2), glm::value_ptr(texcoords[0]), GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
	}

	glGenBuffers(1, &VBO_indices_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_indices_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_polygons*sizeof(glm::uvec3), glm::value_ptr(polygons[0]), GL_STATIC_DRAW);

	sheikki_glBindVertexArray(0);

	/*for(int i = 0; i < num_vertices; ++i)
	{
	for(int j = 0; j < 3; ++j)
	std::cout << vertices[i][j] << " ";
	std::cout << '\n';
	}*/
}

GLuint Model::GetTexture() const
{
	return texture;
}

Model::~Model()
{
	delete[] vertices;
	delete[] normals;
	delete[] polygons;
}
