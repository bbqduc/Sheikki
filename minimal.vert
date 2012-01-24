// Vertex Shader – file "minimal.vert"

#version 330

in vec3 in_Position;
in vec3 in_Normal;	
in vec2 in_TexCoords;

out vec2 texcoord;
out vec4 color;

uniform mat4 MVP;
uniform mat3 N;
uniform mat4 MV;

void main(void)
{
	color = vec4(1.0f,1.0f,1.0f,1.0f);
	texcoord[0] = 1-in_TexCoords[0];
	texcoord[1] = in_TexCoords[1];
	gl_Position = MVP * vec4(in_Position, 1.0);
}
