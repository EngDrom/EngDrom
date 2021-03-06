#version 310 es
precision mediump float;
in vec2 passTCoord;

out vec4 outColor;

uniform sampler2D tex;

void main() {
	outColor = texture(tex, passTCoord);
	
	if (outColor.a < 0.5) {
		discard;
	}
}
