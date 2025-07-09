#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;

out vec3 v_pos;
out vec2 v_uv;

uniform mat4 projViewMat;

void main(){
	v_pos = pos;
	v_uv = uv;
	gl_Position = projViewMat * vec4(pos.x, pos.y, pos.z, 1.0);
}