//#version 420
//laptop only supports 330
//Actually is now able to support 400
#version 330

uniform sampler2D tex;
in vec2 uv;
out vec4 outColor;

void main(){
	outColor = texture(tex, uv);
}
