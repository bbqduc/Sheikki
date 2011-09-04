// Vertex Shader – file "minimal.vert"

#version 120

attribute vec3 in_Position;
attribute vec3 in_Color;	
attribute vec3 in_TexCoords;

varying vec2 texcoord;
varying vec3 ex_Color;
uniform mat4 modelViewMatrix;

void main(void)
{
	texcoord = in_TexCoords.xy;
	ex_Color = in_Color; // vec3(1.0,0.0,1.0);
	gl_Position = modelViewMatrix * vec4(in_Position, 1.0);
}
