#include "graphics.h"
#include "sheikki_wrappers.h"
#include "machineinfo.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>

#define BUFFER_OFFSET(i) ((char*)NULL + i)

	Graphics::Graphics()
{
	perspective=glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);
	initGlew();
	initGL();
	defaultShader.init();
	explosionShader.init();
	phongShader.init();
	//	initFonts();
}

void Graphics::initFonts()
{
	/*	if(FT_Init_FreeType(&fontLibrary))
		std::cerr << "Font library init failed!\n";
		if(FT_New_Face(&fontLibrary, "FreeMono.ttf", 0, &fontInfo))
		std::cerr << "Could not load font!\n";
		FT_Set_Char_Size(fontinfo, 8, 8, 0, 0);*/
}

void Graphics::initGlew()
{
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		std::cerr << "GLEW INIT FAILED!\n";
		exit(-1);
	}
	else
		std::cerr << "Glew version : " << glewGetString(GLEW_VERSION)
			<< "\nOpengl version : " << glGetString(GL_VERSION) 
			<< "\nShading language version : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

	std::stringstream temp; temp << glGetString(GL_SHADING_LANGUAGE_VERSION);
	temp >> MachineInfo::glsl_version;
	if(MachineInfo::glsl_version >= 3.3)
	{
		std::cerr << "Using version 330 shaders!\n";
	}
	else
	{
		std::cerr << "Using version 120 shaders!\n";
	}

	defaultShader.setShaderPaths("plain.vert", "plain.frag");
	explosionShader.setShaderPaths("explosion.vert", "explosion.frag");
	phongShader.setShaderPaths("phong.vert", "phong.frag");
}

void Graphics::initGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)	

}

void checkGLErrors(std::string functionName){
	GLenum err = glGetError();
	if(err != GL_NO_ERROR)
	{
		std::cerr << functionName << " ERROR: " << gluErrorString(err) << "\n";
		exit(-1);
	}
}

void Graphics::reshape(int w, int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	checkGLErrors("reshape");
}

char* Shader::loadFile(const char *fname, GLint &fSize)
{
	std::ifstream::pos_type size;
	char * memblock;
	std::string text;

	std::ifstream file (fname, std::ios::in|std::ios::binary|std::ios::ate);
	if (file.is_open())
	{
		size = file.tellg();
		fSize = (GLuint) size;
		memblock = new char [size];
		file.seekg (0, std::ios::beg);
		file.read (memblock, size);
		file.close();
		std::cerr << "file " << fname << " loaded" << std::endl;
		text.assign(memblock);
	}
	else
	{
		std::cerr << "Unable to open file " << fname << std::endl;
		exit(1);
	}
	return memblock;
}

void Shader::setShaderPaths(const char* vp, const char* fp)
{
	std::string vertex=vp;
	std::string fragment=fp;
	if(MachineInfo::glsl_version<3.3) vertex+="120";
	if(MachineInfo::glsl_version<3.3) fragment+="120";
	vertex_shader_path=vertex;
	fragment_shader_path=fragment;
}

void Shader::printShaderInfoLog(GLint shader)
{
	int infoLogLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

	checkGLErrors("shaderinfolog");

	if (infoLogLen > 0)
	{
		infoLog = new GLchar[infoLogLen];

		glGetShaderInfoLog(shader,infoLogLen, &charsWritten, infoLog);
		std::cout << "InfoLog:" << std::endl << infoLog << std::endl;
		delete [] infoLog;
	}

	checkGLErrors("shaderinfolog");
}

void Shader::init()
{
	assert(!initialized);
	GLuint f, v;

	char *vs,*fs;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);	

	// load shaders & get length of each
	GLint vlen;
	GLint flen;
	vs = loadFile(vertex_shader_path.c_str(),vlen);
	fs = loadFile(fragment_shader_path.c_str(),flen);

	std::cout << "Vertex shader " << vertex_shader_path << " loaded." << std::endl;
	std::cout << "Fragment shader " << fragment_shader_path << " loaded." << std::endl;

	const char * vv = vs;
	const char * ff = fs;

	glShaderSource(v, 1, &vv,&vlen);
	glShaderSource(f, 1, &ff,&flen);

	GLint compiled;

	glCompileShader(v);
	glGetShaderiv(v, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		std::cout << "Vertex shader not compiled." << std::endl;
		printShaderInfoLog(v);
	} 

	glCompileShader(f);
	glGetShaderiv(f, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		std::cout << "Fragment shader not compiled." << std::endl;
		printShaderInfoLog(f);
	} 

	id = glCreateProgram();

	glAttachShader(id,v);
	glAttachShader(id,f);


	glLinkProgram(id);
	glUseProgram(id);

	printShaderInfoLog(f);
	printShaderInfoLog(v);

	delete [] vs; 
	delete [] fs;

	checkGLErrors("initShaders");

	initialized=true;
}

void Shader::passUniforms(const Entity& e, glm::mat4& perspective)
{
	glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f)); // camera position
	glm::mat4 MV = T * e.getPos() * e.getOrientation(); // adding object position
	glm::mat4 MVP = perspective * MV;
	glm::mat3 N(MV);
	N = glm::transpose(glm::inverse(N));

	// Pass the modelviewmatrix to shader
	glUniformMatrix4fv(GetMVPMatrix(), 1, GL_FALSE, glm::value_ptr(MVP));
	glUniformMatrix3fv(GetNMatrix(), 1, GL_FALSE, glm::value_ptr(N));
	glUniformMatrix4fv(GetMVMatrix(), 1, GL_FALSE, glm::value_ptr(MV));
	checkGLErrors("Shader::passUniforms");
}

void ExplosionShader::passUniforms(glm::mat4& MVP, float timeleft)
{
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));
	glUniform1f(timeleftLoc, timeleft);
}

void Graphics::clearBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::drawPhong(const Entity& e)
{
	sheikki_glBindVertexArray(e.model.VAO_id);
	glUseProgram(phongShader.getId());
	phongShader.passUniforms(e, perspective);
	glBindTexture(GL_TEXTURE_2D, e.GetTexture());
	glDrawElements(GL_TRIANGLES, 3*e.model.num_polygons, GL_UNSIGNED_INT, 0);

	glUseProgram(0);
	
	checkGLErrors("drawPhong");
}

void Graphics::drawExplosion(glm::vec3& position, float lifetime)
{
	glm::mat4 VP = perspective * glm::translate(glm::mat4(1.0f), glm::vec3(0,0,-10));
	glm::mat4 MVP = VP * glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f),glm::vec3(lifetime));
	sheikki_glBindVertexArray(models["sphere"].VAO_id);
	glUseProgram(explosionShader.getId());
	glBindTexture(GL_TEXTURE_2D, models["sphere"].GetTexture());
	explosionShader.passUniforms(MVP, lifetime);
	glDrawElements(GL_TRIANGLES, 3*models["sphere"].num_polygons, GL_UNSIGNED_INT, 0);

	glUseProgram(0);

	checkGLErrors("drawExplosion");
}

void Graphics::addModel(std::string id, Model& model)
{
	models[id] = model;
}

const Model& Graphics::getModel(std::string id)
{
	return models[id];
}
