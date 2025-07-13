#version 330 core

layout(location = 0) in vec4 vertex;

out vec2 v_uv;

uniform mat4 projection;

void main(){
	v_uv = vertex.zw;
	gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
}