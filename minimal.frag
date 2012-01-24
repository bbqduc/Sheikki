// Fragment Shader – file "minimal.frag"

#version 330

uniform sampler2D textures;
smooth in vec2 texcoord;
smooth in vec4 color;
out vec4 out_color;

void main(void)
{
	out_color = texture(textures, texcoord)*color;
}
