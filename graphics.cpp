#include "graphics.h"
#include "matrix_utils.h"
#include "sheikki_wrappers.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>

#define BUFFER_OFFSET(i) ((char*)NULL + i)

	Graphics::Graphics()
:perspective(projectionMatrix(45.0f, 800.0f/600.0f, 1, 10))
{
	perspective = perspective * translationMatrix(0,0,-8);

	initGlew();
	initGL();
	defaultShader.init();
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
	double glsl_version; temp >> glsl_version;
	if(glsl_version >= 3.3)
	{
		std::cerr << "Using version 330 shaders!\n";
		defaultShader.setShaderPaths("minimal.vert", "minimal.frag");
	}
	else
	{
		std::cerr << "Using version 120 shaders!\n";
		defaultShader.setShaderPaths("minimal_120.vert", "minimal_120.frag");
	}
	
}

void Graphics::initGL()
{
	glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)
	glEnable(GL_CULL_FACE);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
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

void Shader::printShaderInfoLog(GLint shader)
{
	int infoLogLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

	checkGLErrors("shaderinfolog");
	// should additionally check for OpenGL errors here

	if (infoLogLen > 0)
	{
		infoLog = new GLchar[infoLogLen];

		glGetShaderInfoLog(shader,infoLogLen, &charsWritten, infoLog);
		std::cout << "InfoLog:" << std::endl << infoLog << std::endl;
		delete [] infoLog;
	}

	// should additionally check for OpenGL errors here
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

	bindAttributes();

	glAttachShader(id,v);
	glAttachShader(id,f);


	glLinkProgram(id);
	glUseProgram(id);

	printShaderInfoLog(f);
	printShaderInfoLog(v);

	setUniformLocations();

	checkGLErrors("initShaders - binding uniforms");

	//assert(MVPLoc != -1);
	//assert(NLoc != -1);

	delete [] vs; // dont forget to free allocated memory
	delete [] fs; // we allocated this in the loadFile function...

	checkGLErrors("initShaders");

	initialized=true;
}

void Graphics::draw(const std::list<std::pair<Entity*, Shader*> >& objects)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(std::list<std::pair<Entity*, Shader*> >::const_iterator i = objects.begin(); i != objects.end(); ++i)
		draw(*i);
}

void Graphics::draw(const std::pair<Entity*, Shader*>& pair)
{
	Entity* e=pair.first;
	Shader* s=pair.second;
	std::cout << "Using default shader: " << (s==NULL) << std::endl;
	if(!s) s=&defaultShader;
	sheikki_glBindVertexArray(e->model->VAO_id);
	std::cout << "Using shader: " << s->getId() << std::endl;
	glUseProgram(s->getId());

	MyMatrix<float,4> MV = e->position * e->orientation;
	MyMatrix<float,4> MVP = perspective * MV;
	MyMatrix<float,3> N = shrink(MV);
	N.transpose();

	// Pass the modelviewmatrix to shader
	glUniformMatrix4fv(s->GetModelviewMatrix(), 1, GL_TRUE, &MVP[0]);
	glUniformMatrix3fv(s->GetNormalMatrix(), 1, GL_TRUE, &N[0]);

	glDrawElements(GL_TRIANGLES, 3*e->model->num_polygons, GL_UNSIGNED_INT, 0);

	glUseProgram(0);

	checkGLErrors("display");
}

