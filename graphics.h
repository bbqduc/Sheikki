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
		virtual void bindAttributes()=0;
		virtual void setUniformLocations()=0;
	public:
		Shader() {}
		Shader(std::string& vp, std::string& fp) : vertex_shader_path(vp), fragment_shader_path(fp) {}
		virtual ~Shader() {}
		char* loadFile(const char*, GLint&); // This is for loading a shader for a file
		void init();
		void setShaderPaths(const char* vp, const char* fp)
		{
			vertex_shader_path=vp;
			fragment_shader_path=fp;
		}
		GLuint getId() const {return id;}
		static void printShaderInfoLog(GLint shader); // Prints information in case something goes wrong

		GLint GetModelviewMatrix() const {return MVPLoc;}
		GLint GetNormalMatrix() const {return NLoc;}
		GLint GetTexture() const {return textureLoc;}
};

class DefaultShader : public Shader
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
		DefaultShader() : Shader() {}
		DefaultShader(std::string& vp, std::string& fp) : Shader(vp,fp) {}
};

class Graphics
{
/*	FT_Libary fontLibrary;
	FT_Face fontInfo;
	FT_Uint charIndex;*/

	MyMatrix<float, 4> perspective;
	DefaultShader defaultShader;

	void initFonts();
	void initGlew();
	void initGL();
	void draw(const Entity&);

	public:
	Graphics();
	void draw(const std::list<std::pair<Entity, GLuint> >&);
	
	void reshape(int width, int height);
};

#endif
