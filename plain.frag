// Fragment Shader – file "minimal.frag"

#version 330

uniform sampler2D textures[1];
in vec2 texcoord;
in vec4 color;
out vec4 out_color;

void main(void)
{
	out_color=color; // vec4(0.6f,0.6f,0.6f,0.6f);
}
