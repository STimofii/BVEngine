#version 330 core

layout(location = 0) in vec4 vertex;

out vec2 v_uv;

uniform mat4 rotation;

void main(){
	v_uv = vertex.zw;
	gl_Position = rotation * vec4(vertex.x, vertex.y, 0.0, 1.0);
}