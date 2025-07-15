#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;

out vec2 v_uv;

uniform mat4 projViewMat;
uniform ivec2 chunkPosition;

void main(){
	v_uv = uv;
	gl_Position = projViewMat * vec4(pos.x + chunkPosition.x, pos.y, pos.z + chunkPosition.y, 1.0);
}