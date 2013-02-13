//#version 420
//laptop only supports 330
//Actually is now able to support 400
#version 330

in vec4 position;
uniform mat4 mvp;

void main(){
	gl_Position = mvp * position;
}
