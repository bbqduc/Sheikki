// Vertex Shader  file "explosion.vert"

#version 330

layout(location=0) in vec3 in_Position;
layout(location=1) in vec2 in_TexCoords;
smooth out float dist;
smooth out vec2 texcoord;

uniform mat4 MVP;
uniform float timeleft;

void main(void)
{
	gl_Position = MVP * vec4(in_Position, 1.0f);
	texcoord[0] = 1-in_TexCoords[0];
	texcoord[1] = in_TexCoords[1];
	//dist = 1.0f / (1.0f + distance(vec3(0.0f), in_Position));
}
