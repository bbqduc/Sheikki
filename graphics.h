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
		virtual void passUniforms(const Entity* e, const glm::mat4& perspective)=0;
};

class SimpleShader : public Shader
{
	friend class Graphics;
	protected:
		virtual void bindAttributes()
		{
			glBindAttribLocation(id,0, "in_Position");
		}
		virtual void setUniformLocations()
		{
			MVPLoc = glGetUniformLocation(id, "MVP");
		}
	public:
		virtual void passUniforms(const Entity* e, const glm::mat4& perspective) // Is passing the perspective stupid?
		{
			glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
			glm::mat4 MV = T * e->getPos() * e->getOrientation();
			glm::mat4 MVP = perspective * MV;

			// Pass the modelviewmatrix to shader
			glUniformMatrix4fv(GetMVPMatrix(), 1, GL_FALSE, glm::value_ptr(MVP));
		}
		SimpleShader() : Shader() {}
		SimpleShader(const char* vp, const char* fp) : Shader(vp,fp) {init();}
};

class PhongShader : public Shader
{
	friend class Graphics;
	protected:
		virtual void bindAttributes()
		{
			glBindAttribLocation(id,0, "in_Position");
			glBindAttribLocation(id,1, "in_Normal");
			glBindAttribLocation(id,2, "in_TexCoords");
		}
		virtual void setUniformLocations()
		{
			MVPLoc = glGetUniformLocation(id, "MVP");
			NLoc = glGetUniformLocation(id, "N");
			MVLoc = glGetUniformLocation(id, "MV");
			textureLoc = glGetUniformLocation(id, "textures[0]");
		}
	public:
		virtual void passUniforms(const Entity* e, const glm::mat4& perspective) // Is passing the perspective stupid?
		{
			glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
			glm::mat4 MV = T * e->getPos() * e->getOrientation();
			glm::mat4 MVP = perspective * MV;
			glm::mat3 N(MV);
			N = glm::transpose(glm::inverse(N));

			// Pass the modelviewmatrix to shader
			glUniformMatrix4fv(GetMVPMatrix(), 1, GL_FALSE, glm::value_ptr(MVP));
			glUniformMatrix3fv(GetNMatrix(), 1, GL_FALSE, glm::value_ptr(N));
			glUniformMatrix4fv(GetMVMatrix(), 1, GL_FALSE, glm::value_ptr(MV));
		}
		PhongShader() : Shader() {}
		PhongShader(const char* vp, const char* fp) : Shader(vp,fp) {init();}
};

class Graphics
{
/*	FT_Libary fontLibrary;
	FT_Face fontInfo;
	FT_Uint charIndex;*/
	std::map<std::string, Model> models;

	SimpleShader defaultShader;

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
	void draw(const Entity*);
};

#endif
