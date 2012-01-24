// Fragment Shader � file "minimal.frag"

#version 330

uniform sampler2D textures[1];
smooth in vec2 texcoord;
smooth in vec4 color;
out vec4 out_color;

void main(void)
{
	out_color=texture2D(textures[0], texcoord)*color;
	out_color-=vec4(0.6f,0.6f,0.6f,0.6f);
}
