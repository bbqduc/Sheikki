// Fragment Shader – file "minimal.frag"

#version 330

uniform sampler2D textures[1];
smooth in vec2 texcoord;
smooth in vec3 vVaryingLightDir;
smooth in vec3 vVaryingNormal;
out vec4 vFragColor;

void main(void) {
	vec4 ambientColor = vec4(0.2f,0.2f,0.2f,1.0f);
	vec4 diffuseColor = vec4(1.0f,1.0f,1.0f,0.0f);
	vec4 specularColor = vec4(0.2f,0.2f,0.2f,1.0f);
	float diff = max(0.0, dot(normalize(vVaryingNormal), normalize(vVaryingLightDir)));
	vFragColor = diff * diffuseColor;
	vFragColor += ambientColor;
	vec3 vReflection = normalize(reflect(-normalize(vVaryingLightDir),normalize(vVaryingNormal)));
	float spec = max(0.0, dot(normalize(vVaryingNormal), vReflection));

	if(diff != 0) {
		float fSpec = pow(spec, 32.0);
		vFragColor.rgb += vec3(fSpec, fSpec, fSpec);
	}
	vFragColor *= texture2D(textures[0], texcoord);

}