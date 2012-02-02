// Vertex Shader – file "minimal.vert"

#version 330

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;	
layout(location=2) in vec2 in_TexCoords;

out vec2 texcoord;
smooth out vec3 vVaryingNormal;
smooth out vec3 vVaryingLightDir;

uniform mat4 MVP;
uniform mat3 N;
uniform mat4 MV;

void main(void)
{
	vec4 lightPos = vec4(1.0f,20.0f,1.0f,1.0f);
	vec4 esVertex = MV*vec4(in_Position,1); // eye space vertex
	vec3 esVertex3 = esVertex.xyz / esVertex.w; // eye space vertex
	vec3 L = normalize(lightPos.xyz-esVertex3);
	vec3 Nr = normalize(N*in_Normal);

	texcoord[0] = 1-in_TexCoords[0];
	texcoord[1] = in_TexCoords[1];
	gl_Position = MVP * vec4(in_Position, 1.0);
	vVaryingLightDir = L;
	vVaryingNormal = Nr;
}
