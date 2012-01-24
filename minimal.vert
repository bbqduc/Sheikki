// Vertex Shader – file "minimal.vert"

#version 330

in vec3 in_Position;
in vec3 in_Normal;	
in vec2 in_TexCoords;

out vec2 texcoord;
out vec4 color;

uniform mat4 MVP;
uniform mat3 N;
uniform mat4 MV;

void main(void)
{
	vec4 lightPos = vec4(1.0f,1.0f,1.0f,1.0f);
	vec4 light_ambient = vec4(0.1f, 0.1f, 0.1f, 0.1f);
	vec4 light_diffuse = vec4(1.0f, 1.0f, 1.0f, 0.0f);
	vec4 light_specular = vec4(1.0f, 1.0f, 1.0f, 0.0f);

	float mat_shininess = 1.0f;

	vec4 mat_ambient = vec4(0.1f, 0.1f, 0.1f, 0.0f);
	vec4 mat_diffuse = vec4(1.0f, 1.0f, 1.0f, 0.0f);
	vec4 mat_specular = vec4(0.2f, 0.2f, 0.2f, 0.0f);


	vec4 esVertex = MV*vec4(in_Position,1); // eye space vertex
	vec3 esVertex3 = esVertex.xyz / esVertex.w; // eye space vertex
	vec3 L = normalize(lightPos.xyz-esVertex3);
	vec3 Nr = normalize(N*in_Normal);
	vec3 V = vec3(0,0,1);

	vec3 H = normalize(V+L);
		vec4 A = mat_ambient*light_ambient;
		float diffuse = max(dot(Nr,L),0.0);
		float pf=0;
		if(diffuse != 0.0)
			pf = max( pow(dot(Nr,H), mat_shininess), 0.);

		vec4 S = light_specular*mat_specular*pf;
		vec4 D = diffuse*mat_diffuse*light_diffuse;

	color = A + D + S;
	texcoord[0] = 1-in_TexCoords[0];
	texcoord[1] = in_TexCoords[1];
	gl_Position = MVP * vec4(in_Position, 1.0);
}
