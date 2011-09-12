// Fragment Shader – file "minimal.frag"

#version 330

uniform sampler2D textures[1];
in vec2 texcoord;
in vec3 ex_Normal;
out vec4 color;

void main(void)
{
	color = texture2D(textures[0], texcoord);
	color += vec4(ex_Normal, 1.0f);
}
