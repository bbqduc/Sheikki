#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Window.hpp>

//#include <ft2build.h>
//#include FT_FREETYPE_H

#include <GL/glew.h>
#include "entity.h"
#include <list>

class Graphics
{
/*	FT_Libary fontLibrary;
	FT_Face fontInfo;
	FT_Uint charIndex;*/

	GLint MVPLoc, MVLoc, NLoc;
	GLint textureLoc;
	GLuint shader;

	MyMatrix<float, 4> perspective;

	void initFonts();
	void initGlew();
	void initGL();
	void initShaders();
	char* loadFile(char*, GLint&); // This is for loading a shader for a file
	void printShaderInfoLog(GLint); // Prints information in case something goes wrong
	void draw(const Entity&);

	public:
	Graphics();
	void draw(const std::list<Entity>&);
	
	void reshape(int width, int height);
};

#endif
