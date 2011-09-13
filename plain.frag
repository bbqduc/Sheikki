// Fragment Shader – file "minimal.frag"

#version 330

uniform sampler2D textures[1];
in vec2 texcoord;
in vec3 ex_Normal;
out vec4 color;

void main(void)
{
	color=vec4(0.6f,0.6f,0.6f,0.6f);
}
