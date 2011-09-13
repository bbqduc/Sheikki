#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Window.hpp>

//#include <ft2build.h>
//#include FT_FREETYPE_H

#include <GL/glew.h>
#include "entity.h"
#include <list>
#include <string>

class Shader
{
	protected:
		GLuint id;
		GLint MVPLoc, NLoc;
		GLint textureLoc;

		std::string vertex_shader_path, fragment_shader_path;
		bool initialized;
		virtual void bindAttributes()=0;
		virtual void setUniformLocations()=0;
	public:
		Shader() {initialized=false;}
		Shader(const char* vp, const char* fp)
			: id(0), MVPLoc(0), NLoc(0) {initialized=false;setShaderPaths(vp, fp);}
		virtual ~Shader() {}
		char* loadFile(const char*, GLint&); // This is for loading a shader for a file
		void init();
		void setShaderPaths(const char* vp, const char* fp);
		GLuint getId() const {assert(initialized); return id;}
		static void printShaderInfoLog(GLint shader); // Prints information in case something goes wrong

		GLint GetModelviewMatrix() const {assert(initialized); return MVPLoc;}
		GLint GetNormalMatrix() const {assert(initialized); return NLoc;}
		GLint GetTexture() const {assert(initialized); return textureLoc;}
};

class SimpleShader : public Shader
{
	friend class Graphics;
	private:
		void bindAttributes()
		{
			glBindAttribLocation(id,0, "in_Position");
			glBindAttribLocation(id,1, "in_Normal");
			glBindAttribLocation(id,2, "in_TexCoords");
		}
		void setUniformLocations()
		{
			MVPLoc = glGetUniformLocation(id, "MVP");
			NLoc = glGetUniformLocation(id, "N");
			textureLoc = glGetUniformLocation(id, "textures[0]");
		}
	public:
		SimpleShader() : Shader() {}
		SimpleShader(const char* vp, const char* fp) : Shader(vp,fp) {init();}
};

class Graphics
{
/*	FT_Libary fontLibrary;
	FT_Face fontInfo;
	FT_Uint charIndex;*/

	MyMatrix<float, 4> perspective;
	SimpleShader defaultShader;

	void initFonts();
	void initGlew();
	void initGL();
	void draw(const std::pair<Entity*, Shader*>& pair);

	public:
	Graphics();
	void draw(const std::list<std::pair<Entity*, Shader*> >& list);
	
	void reshape(int width, int height);
};

#endif
