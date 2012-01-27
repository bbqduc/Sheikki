// Fragment Shader  file "explosion.frag"

#version 330

uniform float timeleft;

smooth in float dist;
out vec4 vFragColor

void main(void) {
	vFragColor = vec4(1.0f) * dist * timeleft;
}
