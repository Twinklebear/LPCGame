//#version 420
//laptop only supports 330
//Actually is now able to support 400
#version 330

out vec4 outColor;
uniform float width;

void main(){
	float lerpVal = gl_FragCoord.y / width;
	outColor = mix(vec4(0.0f, 0.0f, 1.0f, 1.0f),
		vec4(1.0f, 0.0f, 0.0f, 1.0f), lerpVal);
}
