//#version 420
//laptop only supports 330
//Actually is now able to support 400
#version 330

in vec4 position;
in vec2 texCoord;
out vec2 uv;
uniform mat4 mvp;

void main(){
	gl_Position = mvp * position;
	uv = texCoord;
}
