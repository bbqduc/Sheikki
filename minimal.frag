// Fragment Shader – file "minimal.frag"

#version 330

uniform sampler2D textures[1];
in vec2 texcoord;
in vec3 ex_Normal;
out vec4 color;
uniform float mipmap;

void main(void)
{
	if(mipmap!=0) color = mix(textureLod(textures[0], texcoord, mipmap), (textureLod(textures[0], texcoord, mipmap)), 0.8);
	else color=textureLod(textures[0], texcoord, 0);
	color += vec4(ex_Normal, 1.0f);
}
