#ifdef __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#define FOURCC_DXT1 0x31545844
#define FOURCC_DXT3 0x33545844
#define FOURCC_DXT5 0x35545844

struct DDSData
{
	unsigned int height;
	unsigned int width;
	unsigned int linearsize;
	unsigned int mipmapcount;
	unsigned int fourcc;
	unsigned int format;
};

int parseHeader(FILE* f, unsigned char* header)
{
	char filecode[4];
	fread(filecode,1,4,f);
	if(strncmp(filecode, "DDS ", 4))
	{
		fclose(f);
		return -1;
	}
	fread(header, 124, 1, f);
	return 0;
}
int getFormat(unsigned char* buf, struct DDSData* data)
{
	if(data->fourcc==FOURCC_DXT1) data->format=GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	else if(data->fourcc==FOURCC_DXT3) data->format=GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	else if(data->fourcc==FOURCC_DXT5) data->format=GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	else
	{
		free(buf);
		return -1;
	}
	return 0;
}

GLuint createTexture(unsigned char* buf, struct DDSData* data)
{
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	unsigned int blocksize=(data->format==GL_COMPRESSED_RGBA_S3TC_DXT1_EXT)?8:16;
	unsigned int offset=0;

	// Create mipmaps
	unsigned int level;
	for(level=0; level<data->mipmapcount && (data->width || data->height); ++level)
	{
		unsigned int size=((data->width+3)/4)*((data->height+3)/4)*blocksize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, data->format, data->width, data->height, 0, size, buf+offset);
		offset+=size;
		data->width/=2;
		data->height/=2;
	}
	return tex;
}

GLuint loadDDSTexture(const char* path)
{
	FILE* f;
	f=fopen(path, "rb");
	if(!f)
	{
		fprintf(stderr, "Failed to open file: %s\n", path);
		return 0;
	}

	unsigned char header[124];
	if(parseHeader(f,header)!=0)
	{
		fprintf(stderr, "Failed to parse header.\n");
		return 0;
	}

	struct DDSData data;
	data.height=*(unsigned int*)&(header[8]);
	data.width=*(unsigned int*)&(header[12]);
	data.linearsize=*(unsigned int*)&(header[16]);
	data.mipmapcount=*(unsigned int*)&(header[24]);
	data.fourcc=*(unsigned int*)&(header[80]);

	unsigned char* buf;
	unsigned int bufsize;
	bufsize=data.mipmapcount>1 ? data.linearsize*2 : data.linearsize;
	buf=(unsigned char*)malloc(bufsize*sizeof(unsigned char));
	fread(buf,1,bufsize,f);
	fclose(f);

	unsigned int format;
	if(getFormat(buf, &data)!=0)
	{
		fprintf(stderr, "Failed to get format from FourCC.\n");
		return 0;
	}
	unsigned int components=(data.fourcc==FOURCC_DXT1)?3:4;

	GLuint tex=createTexture(buf, &data);
	free(buf);
	return tex;
}
