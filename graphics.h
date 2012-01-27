#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Window.hpp>

//#include <ft2build.h>
//#include FT_FREETYPE_H
#include <GL/glew.h>
#include "entity.h"
#include <list>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
	protected:
		GLuint id;
		GLint MVPLoc, NLoc, MVLoc;
		GLint textureLoc;

		std::string vertex_shader_path, fragment_shader_path;
		bool initialized;
	public:
		Shader() {initialized=false;}
		Shader(const char* vp, const char* fp)
			: id(0), MVPLoc(0), NLoc(0) {initialized=false;setShaderPaths(vp, fp);}
		~Shader() {}
		char* loadFile(const char*, GLint&); // This is for loading a shader for a file
		void init();
		void setShaderPaths(const char* vp, const char* fp);
		GLuint getId() const {assert(initialized); return id;}
		static void printShaderInfoLog(GLint shader); // Prints information in case something goes wrong

		GLint GetMVPMatrix() const {assert(initialized); return MVPLoc;}
		GLint GetMVMatrix() const {assert(initialized); return MVLoc;}
		GLint GetNMatrix() const {assert(initialized); return NLoc;}
		GLint GetTexture() const {assert(initialized); return textureLoc;}
		void passUniforms(const Entity& e, glm::mat4& perspective);
};

class SimpleShader : public Shader
{
	friend class Graphics;
	protected:
		void bindAttributes()
		{
			glBindAttribLocation(id,0, "in_Position");
			glBindAttribLocation(id,1, "in_Normal");
			glBindAttribLocation(id,2, "in_TexCoords");
		}
		void setUniformLocations()
		{
			MVPLoc = glGetUniformLocation(id, "MVP");				assert(MVPLoc != -1);
			NLoc = glGetUniformLocation(id, "N");					assert(NLoc != -1);
			MVLoc = glGetUniformLocation(id, "MV");					assert(MVLoc != -1);
			textureLoc = glGetUniformLocation(id, "textures[0]");	assert(textureLoc != -1);
			
		}
	public:
		void init() { Shader::init(); bindAttributes(); setUniformLocations(); }
		SimpleShader() : Shader() {}
		SimpleShader(const char* vp, const char* fp) : Shader(vp,fp) {init(); bindAttributes(); setUniformLocations();}
};

class ExplosionShader : public Shader
{
	GLint timeleftLoc;
	friend class Graphics;
	protected:
		void bindAttributes()
		{
			glBindAttribLocation(id,0, "in_Position");
		}
		void setUniformLocations()
		{
			MVPLoc = glGetUniformLocation(id, "MVP");
			timeleftLoc = glGetUniformLocation(id, "timeleft");
		}
	public:
		void init() { Shader::init(); bindAttributes(); setUniformLocations(); }
		ExplosionShader() : Shader() {}
		ExplosionShader(const char* vp, const char* fp) : Shader(vp,fp) {init(); bindAttributes(); setUniformLocations();}
		void passUniforms(glm::mat4& MVP, float timeleft);
};

class Graphics
{
/*	FT_Libary fontLibrary;
	FT_Face fontInfo;
	FT_Uint charIndex;*/
	std::map<std::string, Model> models;

	SimpleShader defaultShader;
	ExplosionShader explosionShader;

	glm::mat4 perspective;

	void initFonts();
	void initGlew();
	void initGL();

	public:
	Graphics();
	void addModel(std::string id, Model& model);
	const Model& getModel(std::string id);

	void reshape(int width, int height);
	void clearBuffers();
	void drawSimple(const Entity&);
	void drawExplosion(glm::vec3& position, float time, float lifetime);

};

#endif
