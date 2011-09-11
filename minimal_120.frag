// Fragment Shader  file "minimal_120.frag"

#version 120

uniform sampler2D textures[1];
varying vec2 texcoord;
varying vec3 ex_Normal;
uniform float mipmap;

void main(void)
{
	if(mipmap!=0) gl_FragColor = mix(texture2DLod(textures[0], texcoord, mipmap), (texture2DLod(textures[0], texcoord, mipmap)), 0.8);
	else gl_FragColor=texture2DLod(textures[0], texcoord, 0);
	gl_FragColor += vec4(ex_Normal, 1.0f);
}
