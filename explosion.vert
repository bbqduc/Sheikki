// Vertex Shader  file "explosion.vert"

#version 330

in vec3 in_Position;
smooth out float dist;

uniform mat4 MVP;
uniform float timeleft;

void main(void)
{
	gl_Position = MVP * vec4(in_Position, 1.0f);
	dist = 1.0f / (1.0f + distance(vec3(0.0f), in_Position));
}
