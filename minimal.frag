// Fragment Shader – file "minimal.frag"

#version 330

uniform sampler2D textures[1];
in vec2 texcoord;
in vec3 ex_Normal;
out vec4 color;

void main(void)
{
	color=mix(textureLod(textures[0], texcoord, gl_FragCoord.z*2), textureLod(textures[0],texcoord, (gl_FragCoord.z*2)+1), mod(gl_FragCoord.z*2,1));
	color += vec4(ex_Normal, 1.0f);
}
