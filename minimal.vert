// Vertex Shader – file "minimal.vert"

#version 330

in vec3 in_Position;
in vec3 in_Normal;	
in vec2 in_TexCoords;

out vec2 texcoord;
out vec3 ex_Normal;
out vec4 pos;
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
