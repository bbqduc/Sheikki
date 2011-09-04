#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include "vec3.h"

class Model
{
	static GLuint fontTexture;

	friend class Graphics;
	int numVertices;
	Vec3 *vertices, *colors, *texcoords;
	GLint drawMode;
	GLuint texture;
	sf::FloatRect texturecoords;
	GLuint VBOid, colorid, texcoordid;
	void InitVBOs();

	public:
	Model(int numVertices, Vec3 *vertices, Vec3 *colors = NULL, GLint drawMode = GL_TRIANGLES);
	Model(int numVertices, Vec3 *vertices, Vec3 *colors, GLint drawMode, std::string texturepath);
	~Model();
	GLuint GetTexture() const;
};



#endif
