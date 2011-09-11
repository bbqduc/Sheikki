#include "graphics.h"
#include "sheikki_wrappers.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <cmath>

#define BUFFER_OFFSET(i) ((char*)NULL + i)

	Graphics::Graphics()
:perspective(projectionMatrix(45.0f, 800.0f/600.0f, 1, 10))
{
	perspective = perspective * translationMatrix(0,0,-8);

	initGlew();
	initGL();
	initShaders();
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
		std::cerr << "GLEW INIT FAILED!\n";
	else
		std::cerr << "Glew version : " << glewGetString(GLEW_VERSION)
			<< "\nOpengl version : " << glGetString(GL_VERSION) 
			<< "\nShading language version : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
}

void Graphics::initGL()
{
	glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)
	glEnable(GL_CULL_FACE);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
//	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
}

void checkGLErrors(std::string functionName){
	GLenum err = glGetError();
	if(err != GL_NO_ERROR)
	{
		std::cerr << functionName << " ERROR!\n" << gluErrorString(err) << "\n";
		exit(-1);
	}
}

void Graphics::reshape(int w, int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	checkGLErrors("reshape");
}

char* Graphics::loadFile(char *fname, GLint &fSize)
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

void Graphics::printShaderInfoLog(GLint shader)
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

void Graphics::initShaders(){
	GLuint f, v;

	char *vs,*fs;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);	

	// load shaders & get length of each
	GLint vlen;
	GLint flen;
	vs = loadFile("minimal.vert",vlen);
	fs = loadFile("minimal.frag",flen);

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

	shader = glCreateProgram();

	glBindAttribLocation(shader,0, "in_Position");
	glBindAttribLocation(shader,1, "in_Color");
	glBindAttribLocation(shader,2, "in_TexCoords");

	glAttachShader(shader,v);
	glAttachShader(shader,f);

	glLinkProgram(shader);
	glUseProgram(shader);

	modelViewMatrixLoc = glGetUniformLocation(shader, "modelViewMatrix");
	textureLoc = glGetUniformLocation(shader, "textures[0]");
	mipmapLoc=glGetUniformLocation(shader, "mipmap");

	if(modelViewMatrixLoc == -1)
		std::cerr << "Couldn't get ModelViewMatrix-location!\n";

	delete [] vs; // dont forget to free allocated memory
	delete [] fs; // we allocated this in the loadFile function...

	checkGLErrors("initShaders");
	printShaderInfoLog(f);
	printShaderInfoLog(v);

}

void Graphics::draw(const std::list<Entity>& objects)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(std::list<Entity>::const_iterator i = objects.begin(); i != objects.end(); ++i)
		draw(*i);
}

void Graphics::draw(const Entity& entity)
{
	sheikki_glBindVertexArray(entity.model->VAO_id);
	glUseProgram(shader);

	MyMatrix modelViewMatrix = perspective * entity.position * entity.orientation;

	//Specify mipmap by z-distance to the camera
	int mipmap=abs(perspective.getZ()-modelViewMatrix.getZ()-perspective.getZ())/4;
	glUniform1f(mipmapLoc, mipmap);

	// Pass the modelviewmatrix to shader
	glUniformMatrix4fv(modelViewMatrixLoc, 1, GL_TRUE, &modelViewMatrix[0]);

	glDrawElements(GL_TRIANGLES, 3*entity.model->num_polygons, GL_UNSIGNED_INT, 0);

	glUseProgram(0);

	checkGLErrors("display");
}

