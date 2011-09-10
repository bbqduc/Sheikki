// Fragment Shader – file "minimal.frag"

#version 120

varying  vec3 ex_Color;
uniform sampler2D textures[1];
varying vec2 texcoord;

void main(void)
{
	gl_FragColor = texture2DLod(textures[0], texcoord, 0);	// Last parameter specifies the mipmap to use.
	gl_FragColor += vec4(ex_Color, 1.0);
	//gl_FragColor = vec4(ex_Color,1.0);
	
	// Try replacing the above with the following:
	//vec3 tmp_Color;
	//tmp_Color = ex_Color.rrr;	
	//out_Color = vec4(tmp_Color,1.0);
}
