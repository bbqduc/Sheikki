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
		GLint MVPLoc, NLoc, MVLoc;
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

		GLint GetMVPMatrix() const {assert(initialized); return MVPLoc;}
		GLint GetMVMatrix() const {assert(initialized); return MVLoc;}
		GLint GetNMatrix() const {assert(initialized); return NLoc;}
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
			MVLoc = glGetUniformLocation(id, "MV");
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
	std::map<std::string, Model> models;

	glm::mat4 perspective;
	SimpleShader defaultShader;

	void initFonts();
	void initGlew();
	void initGL();

	public:
	Graphics();
	void addModel(std::string id, Model& model);
	const Model& getModel(std::string id);

	void reshape(int width, int height);
	void clearBuffers();
	void draw(const Entity*);

};

#endif
