#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Window.hpp>

//#include <ft2build.h>
//#include FT_FREETYPE_H

#include <GL/glew.h>
#include "entity.h"
#include <list>
#include <string>

class Graphics
{
/*	FT_Libary fontLibrary;
	FT_Face fontInfo;
	FT_Uint charIndex;*/

	GLint MVPLoc, MVLoc, NLoc;
	GLint textureLoc;
	GLint mipmapLoc;
	GLuint shader;

	std::string vertex_shader_path, fragment_shader_path;
	MyMatrix<float, 4> perspective;

	void initFonts();
	void initGlew();
	void initGL();
	void initShaders();
	char* loadFile(const char*, GLint&); // This is for loading a shader for a file
	void printShaderInfoLog(GLint); // Prints information in case something goes wrong
	void draw(const Entity&);

	public:
	Graphics();
	void draw(const std::list<Entity>&);
	
	void reshape(int width, int height);
};

#endif
