// Fragment Shader – file "minimal.frag"

#version 330

uniform sampler2D textures[1];
in vec2 texcoord;
in vec3 ex_Normal;

void main(void)
{
	gl_FragColor = texture2D(textures[0], texcoord) + vec4(ex_Normal, 1.0f);
}
