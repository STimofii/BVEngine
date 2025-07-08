#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;

out vec4 vColor;

void main(){
	vColor = vec4(uv.x, uv.y, 0.0, 1.0);
	gl_Position = vec4(pos, 1.0);
}