// Fragment Shader  file "explosion.frag"

#version 330

uniform sampler2D textures[1];
smooth in vec2 texcoord;
uniform float timeleft;

smooth in float dist;
out vec4 vFragColor;

void main(void) {
	vFragColor = texture2D(textures[0], texcoord) * (vec4(1.0f) * timeleft);
}
