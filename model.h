#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <string>
#include "vec.h"
#include <iosfwd>
#include <stdint.h>

class Model
{
	static GLuint fontTexture;
	std::string name; // This doesn't really have any function

	friend class Graphics;
	friend class Model_Loader_3ds;
	int num_vertices, num_polygons;
	Vec<float, 3> *vertices, *normals;
	Vec<float, 2> *texcoords;
	Vec<GLuint, 3> *polygons;
	GLint drawMode;
	GLuint texture;
	sf::FloatRect texturecoords;
	GLuint VBO_vertices_id, VBO_normals_id, VBO_indices_id, VBO_color_id, VBO_texcoord_id, VAO_id;

	void calculate_normals();
	void InitVBOs();
	void Init_Texture(const std::string& texturepath);
	Model();

	public:
	Model(int num_vertices, int num_polygons, Vec<float, 3> *vertices, Vec<GLuint, 3> *polygons, GLint drawMode = GL_TRIANGLES);
	Model(int num_vertices, int num_polygons, Vec<float, 3> *vertices, Vec<GLuint, 3> *polygons, Vec<float, 2> *texcoords, GLint drawMode, std::string texturepath);
	~Model();
	GLuint GetTexture() const;
};



#endif
