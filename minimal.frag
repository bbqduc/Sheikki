// Fragment Shader – file "minimal.frag"

#version 330

uniform sampler2D textures[1];
in vec2 texcoord;
in vec3 ex_Normal;
in vec4 pos;
out vec4 color;
float mipmap;

void main(void)
{
	mipmap=pos.z/3;
	if(mipmap>0) color = mix(textureLod(textures[0], texcoord, mipmap), (textureLod(textures[0], texcoord, mipmap+1)), 0.5);
	else color=texture2D(textures[0], texcoord);
	color += vec4(ex_Normal, 1.0f);
}
