#version 330 core

layout(location = 0) in vec3 pos;

out vec4 vColor;

void main(){
	vColor = vec4(pos, 1.0);
	gl_Position = vec4(pos, 1.0);
}