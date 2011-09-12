// Vertex Shader  file "minimal_120.vert"

#version 120

attribute vec3 in_Position;
attribute vec3 in_Normal;	
attribute vec2 in_TexCoords;

varying vec2 texcoord;
varying vec3 ex_Normal;
varying vec4 pos;
uniform mat4 MVP;
uniform mat3 N;
//uniform mat4 MV;

void main(void)
{
	texcoord[0] = 1-in_TexCoords[0];
	texcoord[1] = in_TexCoords[1];
	ex_Normal = N * in_Normal;
	gl_Position = MVP * vec4(in_Position, 1.0);
	pos=gl_Position;
}
