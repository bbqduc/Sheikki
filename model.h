#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <string>
#include <iosfwd>
#include <stdint.h>
#include <glm/glm.hpp>

class Model
{
	static GLuint fontTexture;
	std::string name; // This doesn't really have any function

	friend class Graphics;
	friend class Model_Loader_3ds;
	int num_vertices, num_polygons;
	glm::vec3* vertices, *normals;
	glm::vec2* texcoords;
	glm::uvec3* polygons;
	
	GLint drawMode;
	GLuint texture;
	sf::FloatRect texturecoords;
	GLuint VBO_vertices_id, VBO_normals_id, VBO_indices_id, VBO_color_id, VBO_texcoord_id, VAO_id;

	void calculate_normals();
	void InitVBOs();
	void Init_Texture(const std::string& texturepath);
	Model();

	public:
		Model(int num_vertices, int num_polygons, glm::vec3 *vertices, glm::uvec3 *polygons, GLint drawMode = GL_TRIANGLES);
		Model(int num_vertices, int num_polygons, glm::vec3 *vertices, glm::uvec3 *polygons, glm::vec2 *texcoords, GLint drawMode, std::string texturepath);
	~Model();
	GLuint GetTexture() const;
};



#endif
