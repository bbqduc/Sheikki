// Fragment Shader  file "minimal_120.frag"

#version 120

uniform sampler2D textures[1];
varying vec2 texcoord;
varying vec3 ex_Normal;

void main(void)
{
	gl_FragColor=mix(texture2DLod(textures[0], texcoord, gl_FragCoord.z*2), texture2DLod(textures[0],texcoord, (gl_FragCoord.z*2)+1), mod(gl_FragCoord.z*2,1));
	gl_FragColor += vec4(ex_Normal, 1.0f);
}
