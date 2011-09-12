// Fragment Shader  file "minimal_120.frag"

#version 120

uniform sampler2D textures[1];
varying vec2 texcoord;
varying vec3 ex_Normal;

void main(void)
{
	mipmap=pos.z/3;
	if(mipmap!=0) gl_FragColor = mix(texture2DLod(textures[0], texcoord, mipmap), (texture2DLod(textures[0], texcoord, mipmap+1)), 0.5);
	else gl_FragColor=texture2D(textures[0], texcoord);
	gl_FragColor += vec4(ex_Normal, 1.0f);
}
